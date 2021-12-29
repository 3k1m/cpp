/**
@file detector.cpp 
@brief uses the File_Comparisons class to identify possible code plagiarism situations for code stored in separate submission directories  
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
@details based on user choices or defaults, the program does the following: 
(1) identify all pairs of directories; 
(2) identifies all suitable files (based on file extension) within those separate directories to compare against the files within all other directories; 
(3) between each pair of directories, all files are compared against each other by each file being tokenized by encoding specially chosen keywords and elements of the language grammar (while ignoring all comments and content within strings);
(4) files are matched to their best matching file in each directory against which they are compared and the directories themselves are scored for similarity;
(5) the distribution of similarity scores is shown and the directories whose similarity matches a sufficient threshold are displayed with their best matching files listed and the regions of overlap displayed.
NOTE 1: this should work across many different programming languages as the format of comments, quotations, keywords, and file extensions are customizable.
NOTE 2: the user can control many features of the program including where the document directories for comparison are stored; where the support files specifying keywords, syntax, etc., are stored; the threshold at which directories should be displayed; the sensitivity of overlap patch for identical content to be deemed significant; the destination of where results should be written to; the similarity scoring mechansism between documents with overlap based on the longest common sequence, longest common subsequence, or longest common sequences split in a greedy fashion without overlap in either document; the ordering of displayed results (increasing or decreasing similarity); the choice of filler for words that are not tokenized; and whether directory similarities are based on the mean or maximum of their corresponding file pairings.
*/

#include<filesystem>
#include "file_compare.h"

int main(int argc, char** argv)
{

	// find out what information was given 
	// allow for:
	// -dX - document directory X, 'Submissions' by default 
	// -sX - support files in directory X, 'Support' by default 
	// -tX - threshold of X (from 0 to 1), 0.9 by default 
	// -wX - distance/window X from top, 0 by default 
	// -rX - result file X, 'res.txt' by default 
	// -uX - use X for fraction overlap where X='seq' or 'sub' or 'spl'
	// -oX - order by X where X='asc' or 'des'
	// -fX - use X as a filler when a word does not belong to the vocabulary
	// -mX - use X as the directory pair score where X='max' or 'mean'
	
	constexpr int arg_max = 10; // cannot exceed 9 arguments
	if(argc > arg_max){ // too many arguments given
		throw std::logic_error("too many options");
	}
	
	std::string document_loc = "./Docs";
	std::string support_loc = "./Support";
	std::string thresh = "0.8";
	std::string dist = "0";
	std::string results = "./Results/res.txt";
	std::string sort = "asc";
	std::string use = "spl";
	std::string fill = "@";
	std::string directory_score = "mean";
	
	constexpr size_t dash_pos = 0; // where - should be 
	constexpr size_t command_pos = 1; // where the command should be 
	constexpr size_t offset = 2; // depth within options where value found 
	
	// update some 
	for(int i=1; i < argc; ++i){ // look at each argument
		if(argv[i][dash_pos] != '-'){
			throw std::logic_error("invalid stem provided with " + std::string(argv[i]));
		}
		switch (argv[i][command_pos]){ // next argument gives information 
			case 'd': document_loc = argv[i]+offset; break;
			case 's': support_loc = argv[i]+offset; break;
			case 't': thresh = argv[i]+offset; break;
			case 'w': dist = argv[i]+offset; break;
			case 'r': results = argv[i]+offset; break;
			case 'o': sort = argv[i]+offset; break;
			case 'u': use = argv[i]+offset; break;
			case 'f': fill = argv[i]+offset; break;
			case 'm': directory_score = argv[i] + offset; break;
			default: throw std::logic_error("invalid stem provided with " + std::string(argv[i]));			
		}
	}
	
	
	const double thresh_value = std::stod( thresh );
	
	comp::File_Comparisons::Settings opt{};
	
	if( sort == "des" ){ // descending 
		opt = opt | comp::File_Comparisons::Settings::sort_descending;
	}
	else if (sort != "asc"){ // bad input 
		throw std::runtime_error("invalid choice for -o stem");
	}

	if (directory_score == "max") { // use the max 
		opt = opt | comp::File_Comparisons::Settings::rank_max;
	}
	else if (directory_score != "mean") { // bad input 
		throw std::runtime_error("invalid choice for -m stem");
	}
	
	if( use == "sub" ){ // common subsequence 
		opt = opt | comp::File_Comparisons::Settings::score_subsequence;
	}
	else if( use == "seq" ){ // common sequence 
		opt = opt | comp::File_Comparisons::Settings::score_full_sequence;
	}
	else if(use == "spl"){ // split sequence 
		opt = opt | comp::File_Comparisons::Settings::score_split_sequence;
	}
	else { // bad input 
		throw std::runtime_error("invalid choice for -u stem");
	}	
	
	const size_t dist_value = std::stoull( dist );

	const std::filesystem::path support_path(support_loc);

	comp::File_Comparisons sims( document_loc, results, support_path, thresh_value, fill, opt, dist_value );
			
	sims.print_results();
	
	return 0;
} 
