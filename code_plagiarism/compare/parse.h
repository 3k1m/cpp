/**
@file parse.h provides the interface for many functions pertaining to parsing source code
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/

#ifndef _COMP__PARSE_
#define _COMP__PARSE_

#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<fstream>
#include<filesystem>
#include<algorithm>
#include<optional>

#include "trie.h"

namespace comp {

	/**
	determines if given char is whitespace
	@param c the char to check
	@return if the char is a space, new line, or tab
	*/
	constexpr bool is_whitespace(char c) noexcept;
	
	/**
	reads from a stream to compute the next string in a source file
	@param is the stream
	@param punct the punctuation used
	@param comments the starts/ends of comments 
	@param quotes the quotation marks
	@return the next strings as the next string (possibly empty if at end of file) and an optional second string in the case of punctuation 
	*/
	std::pair<std::string, std::optional<std::string>> get_next(std::istream& is, const std::unordered_set<char>& punct , const std::unordered_map<std::string, std::optional<std::string>>& comments, const std::unordered_set<char>& quotes);
	
	/**
	computes relevent encodings and decodings for code
	@param keyword_filename the name of a file with all the keywords
	@param punct all the chars that make up punctuation in the language(s)
	@param fail_value the value to assign when a sequence is not found
	@return a pair consisting of a trie (for the strings and their codes) and an unordered_map (for the code mapping to a string)
	*/
	std::pair< data::trie<char, int>, std::unordered_map<int, std::string> > get_vocabulary(const std::string& keyword_filename, const std::unordered_set<char>& punct, int fail_value);

	/**
	establishes the punctuation in the language
	@param punctuation_filename the name of the file with punctuation marks
	@return all punctuation marks
	*/
	std::unordered_set<char> get_punctuation(const std::string& punctuation_filename);

	/**
	establishes the valid file extensions for the language(s)
	@param ext_filename the name of the file storing valid extensions
	@return all the valid extensions
	*/
	std::unordered_set<std::string> get_extensions(const std::string& ext_filename);

	/**
	establishes the code comment format
	@param comments_filename the name of the file representing comments
	@return pairs of strings of the beginnings (built sequentially) and endings (if not nullopt) -- empty string means single line comment 
	*/
	std::unordered_map<std::string, std::optional<std::string>> get_comments(const std::string& comments_filename);

	/**
	establishes the code quotation symbols
	@param quotes_filename the name of the file representing quotation start/ends
	@return the quotation symbols used in the language  
	*/
	std::unordered_set<char> get_quotes(const std::string& quotes_filename);	
	
	/**
	handles possible comments in code, either moving past them or returning the
	stream to its starting state if there is not a comment
	@param is the stream 
	@param start_ends the comment data 
	*/
	void handle_comments(std::istream& is, const std::unordered_map<std::string, std::optional<std::string>>& start_ends);
	
	/**
	handles possible quotations in code, eitherr moving past them or returning the stream to its starting state if there is not a comment 
	@param is the stream
	@param quotes the quotation marks 
	*/
	void handle_quotations(std::istream& is, const std::unordered_set<char>& quotes);
	
	
	/**
	tokenizes a file to establish its encoding
	@param filename the name of the file to encode
	@param tokens a trie where sequences of chars map to ints
	@param punct all the punctuation
	@param comments the starts/ends of comments 
	@param quotes the quotation marks 
	@return the encoding as a sequence of ints
	*/
	std::vector<int> tokenize(const std::string& filename, const data::trie<char, int>& tokens, const std::unordered_set<char>& punct, const std::unordered_map<std::string, std::optional<std::string>>& comments, const std::unordered_set<char>& quotes);

	/**
	determines if a filename ends with a given extension
	@param test the filename to test
	@param end the ending
	@return if the file does end with that ending
	*/
	bool ends_with(const std::string& test, const std::string& end) noexcept;

	/**
	determines if a filename has an acceptable ending
	@param test the filename to test
	@param ends all permissible endings
	@return if it satisfies at least one of the endings
	*/
	bool correct_ending(const std::string& test, const std::unordered_set< std::string>& ends) noexcept;

	constexpr bool is_whitespace(char c) noexcept {
		return (c == ' ') || (c == '\n') || (c == '\t');
	}

}


#endif
