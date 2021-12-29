/**
@file file_compare.cpp gives implementations for a File_Comparisons class that compares source code in
different directories
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/

#include "file_compare.h"

#include<iomanip>
#include<cmath>
#include<numeric>
#include<map>
#include<unordered_map>

namespace comp {

	File_Comparisons::File_Comparisons(std::string _directory_name, std::string _output_file, const std::filesystem::path& support_path, double _thresh, std::string _filler, File_Comparisons::Settings _opts, size_t _num) :
		directory_name(std::move(_directory_name)),
		output_file(std::move(_output_file)),
		punctuation(get_punctuation(support_path / "punct.txt")),
		extensions(get_extensions(support_path / "exts.txt")),
		comments(get_comments(support_path / "comments.txt")),
		quotes(get_quotes(support_path/ "quotes.txt")),
		thresh(_thresh), filler(std::move(_filler)), opts(_opts), num(_num),
		histogram(hist_num_bins, hist_num_tokens, hist_low, hist_high)
	{		
		handle_logic(support_path / "keywords.txt");
	}


	auto File_Comparisons::get_directory_pairings(const std::vector< std::filesystem::path >& directories) const {
		namespace fs = std::filesystem;

		std::vector<std::pair<fs::path, fs::path>> directory_pairings;

		// i indexes all directories 
		for (size_t i = 0, sz = directories.size(); i < sz; ++i) {
			for (size_t j = i + 1; j < sz; ++j) { // j indexes all directories above i 
				directory_pairings.emplace_back(directories[i], directories[j]);
			}
		}

		return directory_pairings;
	}

	std::vector< std::filesystem::path > File_Comparisons::get_submission_directories() const {
		namespace fs = std::filesystem;

		std::vector<fs::path> submission_directories;

		fs::path rel{ directory_name }; // the path relative to program	
		fs::directory_iterator iter{ rel };


		for (const auto& e : iter) { // loop through the submission directory 
			if (e.is_directory()) { // only add if directory 
				submission_directories.push_back(e.path());
			}
		}

		return submission_directories;
	}

	auto File_Comparisons::get_file_pairings(const std::vector<std::pair<std::filesystem::path, std::filesystem::path>>& directory_pairings) const {
		namespace fs = std::filesystem;

		std::vector<std::pair<fs::path, fs::path>> file_pairings;

		for (const auto& [left, right] : directory_pairings) { // for each pairing of directories

			for (const auto& f1 : fs::directory_iterator(left)) { // loop through first directory 
				// require that entry is a file and has the correct extension 
				if (f1.is_regular_file() && correct_ending(f1.path().filename().string(), extensions)) {
					// loop through second directory 
					for (const auto& f2 : fs::directory_iterator(right)) {
						// requirer that entry is a file and has the correct extension 
						if (f2.is_regular_file() && correct_ending(f2.path().filename().string(), extensions)) {
							file_pairings.emplace_back(f1, f2);
						}
					}
				}
			}
		}

		return file_pairings;
	}




	void File_Comparisons::initialize_vocab(const std::string& keywords_file) {
		constexpr int fail_val = -1;
		auto vocab = get_vocabulary(keywords_file, punctuation, fail_val);
		tokens = std::move(vocab.first);
		key_to_word = std::move(vocab.second);
		key_to_word[fail_val] = filler;
	}

	auto File_Comparisons::get_sorted_file_pairings() const {
		auto all_dirs = get_submission_directories();
		auto dir_pairs = get_directory_pairings(all_dirs);
		auto file_pairs = get_file_pairings(dir_pairs);

		std::sort(file_pairs.begin(), file_pairs.end(), [](const auto& p1, const auto& p2) { // order by the first string
			return p1.first.string() < p2.first.string();
			});

		return file_pairs;
	}

	auto File_Comparisons::get_dir_pairs_with_file_pairs(
		const std::vector<std::pair<std::filesystem::path, std::filesystem::path>>& directory_pairings) const {

		namespace fs = std::filesystem;

		std::map<std::string, std::vector<std::pair<fs::path, fs::path>>> dir_pairs_with_file_pairs;

		for (const auto& [left, right] : directory_pairings) { // for each pairing of directories
			std::string label = left.string() + "-" + right.string();

			for (const auto& f1 : fs::directory_iterator(left)) { // loop through first directory 
				// require that entry is a file and has the correct extension 
				if (f1.is_regular_file() && correct_ending(f1.path().filename().string(), extensions)) {
					// loop through second directory 
					for (const auto& f2 : fs::directory_iterator(right)) {
						// requirer that entry is a file and has the correct extension 
						if (f2.is_regular_file() && correct_ending(f2.path().filename().string(), extensions)) {
							dir_pairs_with_file_pairs[label].emplace_back(f1, f2);
						}
					}
				}
			}
		}

		return dir_pairs_with_file_pairs;
	}

	void File_Comparisons::handle_logic(const std::string& keywords_file) {
		initialize_vocab(keywords_file);

		auto all_dirs = get_submission_directories();
		auto dir_pairs = get_directory_pairings(all_dirs);
		auto files_to_compare = get_dir_pairs_with_file_pairs(dir_pairs);

		do_comparisons(files_to_compare);
	}

	void File_Comparisons::do_comparisons(const std::map<std::string, std::vector<std::pair<std::filesystem::path,
		std::filesystem::path>>>& dir_pairs_with_files) {

		namespace fs = std::filesystem;
		
		if (dir_pairs_with_files.empty()) { // have no pairs of directories 
			std::cout << "No files to compare!\n";
			return;
		}

		Sequence_Comps<int>::Scoring score_choice{}; // let it start at 0 
		if (static_cast<unsigned char>(opts) & static_cast<unsigned char>(Settings::score_full_sequence)) {
			score_choice = Sequence_Comps<int>::Scoring::sequence;
		}
		else if (static_cast<unsigned char>(opts) & static_cast<unsigned char>(Settings::score_subsequence)) {
			score_choice = Sequence_Comps<int>::Scoring::subsequence;
		}
		else {
			score_choice = Sequence_Comps<int>::Scoring::split_sequence;
		}

		const size_t tot_to_compare = std::accumulate(dir_pairs_with_files.begin(), dir_pairs_with_files.end(),
			static_cast<size_t>(0), [](size_t s, const auto& p) {
				return s += p.second.size();
			});


		std::vector<int> encoded_left; // keep record of previous tokens when left repeats
		std::string left_string; // left string

		size_t curr = 0; // current comparison number 
		const size_t chunk = std::max<size_t>(1, tot_to_compare / 10);
		
		// dirs gives directories and file_pairs are all pairings under those directories 
		for (const auto& [dirs, file_pairs] : dir_pairs_with_files) { // directories with vector list

			std::map<fs::path, std::map<double, fs::path>> file_matches;
			std::map<std::pair<fs::path, fs::path>, Sequence_Comps<int>> pairs_with_comps;

			// iterate over pair dirs 
			for (const auto& [left, right] : file_pairs) { // pairs of files

				if (++curr % chunk == 0) { // give periodic updates 
					std::cout << "handling comparison " << curr << " of " << tot_to_compare << 
						" total file pairings " << std::endl; // force buffer flush 
				}

				std::string label = left.string() + "-" + right.string();

				if (left.string() != left_string) { // if left file updates
					// update both the string and the encoding 
					left_string = left.string();
					encoded_left = tokenize(left.string(), tokens, punctuation, comments, quotes);
				}

				// encode right file 
				auto encoded_right = tokenize(right.string(), tokens, punctuation, comments, quotes);

				// initiate comparison			
				Sequence_Comps comp{ label, encoded_left, encoded_right, score_choice, num };
				

				// how much the two overlap 
				const double overlap = comp.fraction_overlap();

				// must be reciprocal
				file_matches[left][overlap] = right;
				file_matches[right][overlap] = left;

				// stores the comparison
				pairs_with_comps.emplace(std::make_pair(left, right), std::move(comp));
			}
			
			std::map<fs::path, fs::path> merged;
			for (const auto& [f, score_file] : file_matches) { // file with its scores with other files 
				// best matching file to f
				const auto& f_map = score_file.crbegin()->second;
				
				if(merged.count(f_map)==0){ // f_map not already a key 
					merged[f]=f_map;
				}
				else if( file_matches.at(f_map).crbegin()->second != f){ // f_map is a key, but f_map does not map to f 
					merged[f] = f_map;
				}
			}
			
			// now test this directory pairing and score it
			double mean = 0;
			double max = 0;
			for (const auto& [left, right] : merged) { // over all matches
				auto left_right = std::make_pair(left, right);
				if (pairs_with_comps.count(left_right) > 0) { // matches with left first
					const double curr = pairs_with_comps.at(left_right).fraction_overlap();
					mean += curr;
					max = (max < curr ? curr : max);
					continue;
				}
				auto right_left = std::make_pair(right, left);
				if (pairs_with_comps.count(right_left) > 0) { // matches with right first 
					const double curr = pairs_with_comps.at(right_left).fraction_overlap();
					mean += curr;
					max = (max < curr ? curr : max);
				}
			}
			mean /= merged.size();

			const bool rank_max = static_cast<unsigned char>(Settings::rank_max)& static_cast<unsigned char>(opts);
			
			// score is either the mean or the max
			const double score = (rank_max ? max : mean);

			histogram.insert(score);

			// good enough to keep 
			if (score > thresh) {
				// set the score space before adding the file matches
				most_similar.emplace_back(dirs, std::make_pair(score, std::vector<Sequence_Comps<int>>{}));
				for (const auto& [left, right] : merged) { // over all matches
					auto left_right = std::make_pair(left, right);
					auto& ate = most_similar.back().second.second;
					if (pairs_with_comps.count(left_right) > 0) { // matches with left first 
						ate.push_back(std::move(pairs_with_comps.at(left_right)));
						continue;
					}
					auto right_left = std::make_pair(right, left);
					if (pairs_with_comps.count(right_left) > 0) { // matches with right first 
						ate.push_back(std::move(pairs_with_comps.at(right_left)));
					}
				}
			}
		}


		// determine if sorting ascending or descending
		bool sort_desc = static_cast<unsigned char>(Settings::sort_descending) & static_cast<unsigned char>(opts);

		if (sort_desc) { // reverse iterators reverse sorting
			std::sort(most_similar.rbegin(), most_similar.rend(), [](const auto& x, const auto& y) {
				return x.second.first < y.second.first;
				});
		}
		else {  // normal ascending
			std::sort(most_similar.begin(), most_similar.end(), [](const auto& x, const auto& y) {
				return x.second.first < y.second.first;
				});
		}

	}


	void File_Comparisons::print_results() const {

		namespace fs = std::filesystem;

		if (histogram.size() == 0) {
			std::cout << "No results (perhaps the wrong extensions were specified or the document directory is empty)!\n";
			return;
		}

		constexpr size_t line_width = 50;

		const std::string dashed(line_width, '-');
		const std::string double_dashed(line_width, '=');
		const std::string tilded(line_width, '~');
		constexpr double pct = 100. / hist_num_tokens;

		fs::path rel{ output_file }; // the path relative to program
		fs::path dirs = rel.relative_path().parent_path(); // the relative paths up to the present
		if (!dirs.string().empty()) { // cannot create "" directory so check
			fs::create_directories(dirs);
		}

		std::ofstream fout(rel.string());

		// print out histogram results

		std::cout << "\nThere were " << histogram.size() << " comparisons made between directories. See distribution below (each * token represents " << pct << "% of all comparisons -- an empty bin may indicate zero or negligible counts).\n";
		fout << "There were " << histogram.size() << " comparisons made between directories. See distribution below (each * token represents " << pct << "% of all comparisons -- an empty bin may indicate zero or negligible counts).\n";
		histogram.display(std::cout);
		histogram.display(fout);

		if (most_similar.empty()) { // nothing meets tolerance threshold
			std::cout << '\n' << "There are no results to display that meet the threshold requirement.\n";
			fout << '\n' << "There are no results to display that meet the threshold requirement.\n";
			return;
		}
		std::cout << '\n' << "Various overlaps are displayed below with '" << filler << "' as the placeholder for anything outside of the vocabulary/symbols:\n";
		fout << '\n' << "Various overlaps are displayed below with '" << filler << "' as the placeholder for anything outside of the vocabulary/symbols:\n";
		for (const auto& [dirs, files] : most_similar) { // iterate over top documents
			std::cout << "Directories " << dirs << " with overlap " << files.first << ":\n";
			fout << "Directories " << dirs << " with overlap " << files.first << ":\n";
			for (const auto& m : files.second) { // these are Sequence comparison objects
				std::cout << double_dashed << '\n' << m.get_label() << ":\n";
				fout << double_dashed << '\n' << m.get_label() << ":\n";
				std::cout << "document 1 length: " << m.size1() << '\n';
				std::cout << "document 2 length: " << m.size2() << '\n';
				fout << "document 1 length: " << m.size1() << '\n';
				fout << "document 2 length: " << m.size2() << '\n';
				std::cout << "longest common subsequence: " << m.get_subsequence_score() << '\n';
				fout << "longest common subsequence: " << m.get_subsequence_score() << '\n';
				std::cout << "longest common sequence: " << m.get_sequence_score() << '\n';
				fout << "longest common sequence: " << m.get_sequence_score() << '\n';
				std::cout << "longest common split sequence: " << m.get_split_sequence_score() << '\n';
				fout << "longest common split sequence: " << m.get_split_sequence_score() << '\n';
				std::cout << "fraction overlap: " << m.fraction_overlap() << '\n';
				fout << "fraction overlap: " << m.fraction_overlap() << '\n';

				auto sub = m.get_a_longest_common_subsequence();
				std::cout << "longest common subsequence:\n";
				fout << "longest common subsequence:\n";
				for (const auto& s : sub) { // iterate over longest common subsequence 
					try { // need to use at so hence try 
						const std::string& w = key_to_word.at(s);
						std::cout << w << ' ';
						fout << w << ' ';
					}
					catch (...) {} // handle exception (but shouldn't happen)
				}
				std::cout << '\n' << dashed << '\n';
				fout << '\n' << dashed << '\n';
				auto seq = m.get_longest_common_sequences();
				std::cout << "longest common sequences:\n";
				fout << "longest common sequences:\n";
				for (const auto& ss : seq) { // all common sequences
					for (const auto& s : ss) { // all terms in that sequence 
						try { // using at again so need try
							const std::string& w = key_to_word.at(s);
							std::cout << w << ' ';
							fout << w << ' ';
						}
						catch (...) {} // handle exceptions 
					}
					std::cout << '\n' << tilded << '\n';
					fout << '\n' << tilded << '\n';
				}
				std::cout << double_dashed << '\n';
				fout << double_dashed << '\n';

				auto split = m.get_longest_common_split();
				std::cout << "longest common split sequences:\n";
				fout << "longest common split sequences:\n";
				for (const auto& ss : split) { // all longest common split sequences 				
					for (const auto& s : ss) { // all terms in that sequence 
						try { // using at again so need try
							const std::string& w = key_to_word.at(s);
							std::cout << w << ' ';
							fout << w << ' ';
						}
						catch (...) {} // handle exceptions 
					}
					std::cout << '\n' << tilded << '\n';
					fout << '\n' << tilded << '\n';
				}
				
			}
		}

		fout.close();

	}


}
