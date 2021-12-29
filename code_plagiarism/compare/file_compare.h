/**
@file file_compare.h defines a File_Comparisons class to compare source code between different directories to
detect possible plagiarism
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/

#ifndef _COMP__FILE_COMPARE_
#define _COMP__FILE_COMPARE_

#include<unordered_set>
#include<unordered_map>
#include<string>
#include<filesystem>
#include<vector>

#include "sequence.h"
#include "parse.h"
#include "histogram.h"

namespace comp {

	/**
	The File_Comparisons class handles the comparisons of all source files
	in different directories
	*/
	class File_Comparisons {
	public:
		/**
		@enum Settings represents user choices in
		how data are sorted and how overlaps are computed
		*/
		enum class Settings : unsigned char {
			score_full_sequence = 1 << 0,
			score_subsequence = 1 << 1,
			score_split_sequence = 1 << 2,
			sort_descending = 1 << 3,
			rank_max = 1 << 4
		};

		/**
		operator | between Settings
		@param x the first Settings
		@param y the second Settings
		@return a combination  of the two or an exception is thrown if invalid
		*/
		friend constexpr Settings operator|(const Settings& x, const Settings& y);


		/**
		constructor for File_Comparisons
		@param _directory_name the name of the directory in which to do comparisons
		@param _output_file the name of the file to write to
		@param support_path the path of the directory with 'punct.txt', 'exts.txt', 'keywords.txt', 'comments.txt', and 'quotes.txt'
		@param keywords_file the name of the file with all keywords/vocabulary
		@param _thresh a fractional threshold/cutoff such that all computed results must have overlaps at least this large
		@param _filler what to print with items that are not vocab/punctuation
		@param _opts the options for the fraction overlap computation and the display sorting
		@param _num the minimal length required to document a common sequence
		*/
		File_Comparisons(std::string _directory_name, std::string _output_file, const std::filesystem::path& support_path,
			double _thresh = 0.8, std::string _filler = "@",
			File_Comparisons::Settings _opts = Settings::score_split_sequence | Settings::sort_descending, size_t _num = 5);

		/**
		displays results to console and writes them to the file
		*/
		void print_results() const;

	private:
		std::string directory_name; // directory with directories to scan 
		std::string output_file; // destination to write to 
		std::unordered_set<char> punctuation; // valid punctuation 
		std::unordered_set<std::string> extensions;	// valid extensions 
		std::unordered_map<std::string, std::optional<std::string>> comments; // start/end of comments 
		std::unordered_set<char> quotes; // quotation marks
		double thresh; // fractional threshold at which to include in final results 
		Settings opts; // computation options
		size_t num; // how close to longest common sequence needed for printing
		std::string filler; // what to print when non-vocab/punctuation 

		data::trie<char, int> tokens; // string to int encodings 
		std::unordered_map<int, std::string> key_to_word; // int to string decodings 

		// most similar stored
		std::vector <
			std::pair <
			std::string, std::pair<double, std::vector<Sequence_Comps<int>>
			>>> most_similar;

		data::simple_histogram histogram;
		static constexpr size_t hist_num_bins = 10; // use 10 bins 
		static constexpr size_t hist_num_tokens = 50; // each token worth 2%
		static constexpr double hist_low = 0., hist_high = 1.; // range 0 to 1 

		/**
		finds all directories in which to scan through
		@return a vector of all paths to directories such that files in different
		directories should be compared
		*/
		std::vector< std::filesystem::path > get_submission_directories() const;

		/**
		sets all pairwise comparisons of directories
		@param directories the paths of all the directories in question
		@return a vector storing all pairings of non-equal directories
		*/
		auto get_directory_pairings(const std::vector< std::filesystem::path >& directories) const;

		/**
		for each pair of folders, it pairs all files between those folders
		@param directory_pairings the pairs of directories
		@return a map between the label of the directory pair and a vector of the file parings
		*/
		auto get_dir_pairs_with_file_pairs(
			const std::vector<std::pair<std::filesystem::path, std::filesystem::path>>& directory_pairings) const;


		/**
		determines all files within different directories to compare
		@param directory_pairings the pariings of directories whose files are to be compared
		@return all pairings of files in each directory with files of all other directories
		*/
		auto get_file_pairings(const std::vector<std::pair<std::filesystem::path, std::filesystem::path>>& directory_pairings) const;

		/**
		sets the encodings and decodings
		@param keywords_file the file storing the keywords/vocabulary
		*/
		void initialize_vocab(const std::string& keywords_file);

		/**
		from the submission directory, determines all files to be compared in a sorted order
		@return a vector of all path pairings for files to be compared
		*/
		auto get_sorted_file_pairings() const;

		/**
		does the comparisons of all files and stores the most similar
		@param dir_pairs_with_files the pairings of directories with their pairings of files
		*/
		void do_comparisons(const std::map<std::string, std::vector<std::pair<std::filesystem::path,
			std::filesystem::path>>>& dir_pairs_with_files);


		/**
		handles the logic of the class so all the work gets done
		@param keywords_file the file with the keywords
		*/
		void handle_logic(const std::string& keywords_file);
	};

	constexpr File_Comparisons::Settings
		operator|(const File_Comparisons::Settings& x, const File_Comparisons::Settings& y) {
		unsigned char both = static_cast<unsigned char>(x) | static_cast<unsigned char>(y);

		// only 1 bit from 0-2 should be set
		if (((both >> 0 & 1) + (both >> 1 & 1) + (both >> 2 & 1) > 1)) {
			throw std::logic_error("bad combination of options");
		}

		return static_cast<File_Comparisons::Settings>(both);
	}

}



#endif 
