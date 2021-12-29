/**
@file parse.cpp provides the implementations for functions parsing source code
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/
#include "parse.h"

#include<optional>
#include<unordered_map>

namespace comp {
		
	std::pair<std::string, std::optional<std::string>> get_next(std::istream& is, const std::unordered_set<char>& punct , const std::unordered_map<std::string, std::optional<std::string>>& comments, const std::unordered_set<char>& quotes){
		
		while (!is.eof() && is_whitespace(is.peek())) { // ignore the whitespace 
			is.ignore();
		}
		if (is.eof()) { // end of file means nothing 
			return {"", std::nullopt};
		}
		
		const auto init = is.tellg(); // where in stream		

		// not end of file
		const char p = is.peek();
		if(punct.count(p)>0){ // could be comment, quote, ...
			const auto init = is.tellg(); // where in stream		
			handle_comments(is, comments);
			if(is.tellg() == init){ // not a comment, but maybe a quote 
				handle_quotations(is, quotes);
				if(is.tellg() != init){ // it was a quote, so now past it, but return both quotation marks  
					const std::string qt = std::string{}+p;
					if(!is.eof()){ // was closed, too 
						return {qt,qt}; // need both 
					}
					else{ // only opened 
						return {qt, std::nullopt};
					}
				}
				else{ // not a quote, just a punctuation
					return {std::string(1, is.get()), std::nullopt};
				}
			}
			else{ // it was a comment so move on 				
				return get_next(is, punct, comments, quotes);
			}
		}
		
		if(is.eof()){ // exhausted file
			return {"", std::nullopt};
		}
		
		// just a word 
		std::string res;
		res += is.get();
		
		// keep reading until end of file or whitespace/puntuation encountered 
		while (!is.eof() && !is_whitespace(is.peek()) && punct.count(is.peek()) == 0) {
			res += is.get(); // append char by char 
		}

		return {res,std::nullopt};
	}

	std::pair< data::trie<char, int>, std::unordered_map<int, std::string> > 
		get_vocabulary(const std::string& keyword_filename, const std::unordered_set<char>& punct, int fail_value) {

		// for encoding and decoding 
		data::trie<char, int> tokens{ fail_value };
		std::unordered_map<int, std::string> key_to_word;

		// open and test 
		std::ifstream fin(keyword_filename);
		if (!fin) { // didn't open 
			throw std::runtime_error("missing vocabulary file");
		}

		// read and encode 
		std::string word;
		int code = 0;

		while (fin >> word) { // while more words in file 
			tokens.insert(word, code);
			key_to_word[code++] = word;
		}

		fin.close();

		for (char c : punct) { // also encode all punctuation with values 
			std::string cstr = std::string{}+c;
			tokens.insert(cstr, code);
			key_to_word[code++] = cstr;
		}

		return std::make_pair(tokens, key_to_word);
	}

	std::unordered_set<char> get_punctuation(const std::string& punctuation_filename) {
		std::unordered_set<char> puncts;

		std::ifstream fin(punctuation_filename);
		if (!fin) { // did not open 
			throw std::runtime_error("missing punctuation file");
		}
		char c;
		while (fin >> c) { // read one char at a time 
			puncts.insert(c);
		}
		fin.close();

		return puncts;
	}

	std::unordered_set<std::string> get_extensions(const std::string& ext_filename) {
		std::ifstream fin(ext_filename);

		if (!fin) { // could not open 
			throw std::runtime_error("missing source file");
		}

		std::unordered_set<std::string> exts;
		std::string ext;
		while (fin >> ext) { // read one extension at a time 
			exts.insert(ext);
		}
		fin.close();

		return exts;
	}
	
	std::unordered_map<std::string, std::optional<std::string>> get_comments(const std::string& comments_filename){
		
		std::unordered_map<std::string, std::optional<std::string>> start_ends;
		
		std::ifstream fin(comments_filename);
		if (!fin) { // did not open 
			throw std::runtime_error("missing comment file");
		}
		
		constexpr size_t min_size = 3;
		
		std::string info;
		while(std::getline(fin, info) && !info.empty()){
			if(info.size()<min_size){ // need at least 3: [ something ]
				throw std::runtime_error("bad comment file format");
			}
			
			std::string start, end;
			
			auto open_pos = std::find(info.begin(), info.end(), '[');
			auto close_pos = std::find(info.begin(), info.end(), ']');
			if(open_pos < close_pos && open_pos != info.end() && close_pos != info.end()){ // have [ before ] -- good 
				start = {open_pos+1, close_pos}; // take everything between []				
			}
			else{ // wrong format completely 
				throw std::runtime_error("bad comment file format");
			}
			// try to find another 
			auto next_open_pos = std::find(close_pos,info.end(), '[');
			if(next_open_pos != info.end()){ // was given a close 
				auto next_close_pos = std::find(next_open_pos+1,info.end(),']');
				if(open_pos < close_pos && close_pos != info.end()){ // have [ before ] -- good 
					end = {next_open_pos+1, next_close_pos}; // take everything between []					
				}
				else{ // forgot to close or wrong format 
					throw std::runtime_error("bad comment file format");
				}
			}
			
		
			for(size_t i=1; i <= start.size()-1; ++i){ // iterate over all but full and set ending as nullopt
				start_ends[start.substr(0,i)]; // default constructed = nulllopt
			}
			
			// now add at the end 
			start_ends[start]=end;
		}	

		return start_ends;		
	}
	
	std::unordered_set<char> get_quotes(const std::string& quotes_filename){
		std::unordered_set<char> quotes;
		
		std::ifstream fin(quotes_filename);
		if (!fin) { // did not open 
			throw std::runtime_error("missing quotation file");
		}
		
		char c;
		while(fin >> c){ // keep reading a char 
			quotes.insert(c);
		}
		
		return quotes;
	}
	
	
	void handle_comments(std::istream& is, const std::unordered_map<std::string, std::optional<std::string>>& start_ends){
				
		if(is.eof()){ // do nothing here 
			return;
		}
		
		// position in stream in case we need to go back 
		const auto pos = is.tellg();
		
		// current substring 
		std::string curr( 1, is.get() );
		
		// as long as substring is still in beginning and there is no end 
		while( !is.eof() && start_ends.count(curr)>0 && start_ends.at(curr) == std::nullopt){
			curr += is.get(); // append
		}

	
		if( is.eof() || start_ends.count(curr) == 0){ // then it wasn't a comment after all		
			is.seekg(pos); // go back to start
			return; // finish the work 
		}
		
		// to reach here, the value is not nullopt and hence at start of comment 
		const std::string& end = start_ends.at(curr).value();
		
		if( end.empty()){ // only single line, still room 
			std::string line;
			std::getline(is,line);
			return;
		}
		else if(end.empty()){ // only single line but do nothing b/c EOF 
			return;
		}		
		
		// must be multiline, need to read to the end of it 
		size_t end_len = 1;
		curr.clear();
	
		// use <= because talk of length
		while( !is.eof() && end_len <= end.size() ){ // until we have found a match
			curr += is.get();
			if( end.substr(0, end_len) == curr){ // is a current match 
				++end_len;
			}
			else{ // back to the drawing board
				end_len = 1;
				curr.clear();
			}
		}
		
		return;		
	}
	
	
	void handle_quotations(std::istream& is, const std::unordered_set<char>& quotes){
		if(is.eof()){ // do nothing here 
			return;
		}
		
		const char c = is.get(); // possible quote we started with 
		
		if( quotes.count(c) == 0 ){ // wasn't a quotation
			is.unget(); // go back
			return; // and finish 
		}
		
		bool done = false; // when done reading the quote 
		
		while(!is.eof() && !done){ // until emptied or reached closing quote 
			char n = is.get();
			if(n=='\\'){ // an escape so need to ignore the next, too 
				if(!is.eof()){ // not exhausted, just ignore the next 
					is.ignore();
				}
			}
			else{ // not escaped so check 
				if(n==c){ // reached matching quote, so done 
					done = true;
				}
			}
		}		
	}
		
	
	std::vector<int> tokenize(const std::string& filename, const data::trie<char, int>& tokens, const std::unordered_set<char>& punct, const std::unordered_map<std::string, std::optional<std::string>>& comments, const std::unordered_set<char>& quotes) {
		std::ifstream fin(filename);

		if (!fin) { // could not open 
			throw std::runtime_error("missing source file" + filename);
		}

		std::vector<int> codes;

		std::pair<std::string, std::optional<std::string>> next;
		while (!fin.eof()) { // establish next string and encode it		
			next = get_next(fin, punct,comments,quotes);
			if (!next.first.empty()) { // ignore empty string
				codes.push_back(tokens.get(next.first));
				if(next.second != std::nullopt){ // also need second 
					codes.push_back(tokens.get(next.second.value()));
				}
			}
		}

		fin.close();


		return codes;
	}

	bool ends_with(const std::string& test, const std::string& end) noexcept {
		return end.size() <= test.size() && !end.empty() ? test.substr(test.size() - end.size()) == end : false;
	}

	bool correct_ending(const std::string& test, const std::unordered_set< std::string>& ends) noexcept {
		return std::any_of(ends.begin(), ends.end(), [&test](const std::string& e) {
			return ends_with(test, e);
			});
	}

}
