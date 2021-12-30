/**
@file sequence.h defines a templated class, Sequence_Comps, that can identify the longest common sequence/subsequence beteen two vectors
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/

#ifndef _COMP__SEQUENCE_
#define _COMP__SEQUENCE_

#include <vector>
#include <set>
#include <algorithm>
#include<string>
#include<map>
#include<utility>

namespace comp {

	/**
	@class Sequence_Comps identifies common sequences between two documents represented
	as vectors
	@tparam T the type within the vector
	*/
	template<typename T>
	class [[nodiscard]] Sequence_Comps {
	public:
		enum class Scoring : unsigned char {
			subsequence = 1 << 0,
			sequence = 1 << 1,
			split_sequence = 1 << 2
		};

		/**
		constructor for the class
		@param _label the label to give to the results
		@param _doc1 the first document
		@param _doc2 the second document
		@param _choice if the scoring is done by the longest common subsequence, longest common sequence, or a greedy sum of the longest common sequences
		@param _tol_window sets how many sequences or sequence components to compute that are no farther than num from the maximum length
		*/
		Sequence_Comps(std::string _label, const std::vector<T>& _doc1, const std::vector<T>& _doc2, Scoring _choice = Scoring::sequence, size_t _tol_window = 1);

		/**
		gives the label
		@return the label given
		*/
		const std::string& get_label() const noexcept;

		/**
		query size of first document
		@return the size of document 1, where value 1 means empty
		*/
		size_t size1() const noexcept;

		/**
		query size of second document
		@return the size of document 2, where value 1 means empty
		*/
		size_t size2() const noexcept;

		/**
		gets the subsequence score
		@return the length of the longest common subsequence
		*/
		size_t get_subsequence_score() const noexcept;

		/**
		gets the sequence score
		@return the length of the longest common sequence
		*/
		size_t get_sequence_score() const noexcept;

		/**
		gets the sequence score
		@return the length of the longest common sequences
		from a greedy method
		*/
		size_t get_split_sequence_score() const noexcept;

		/**
		assesses the fraction overlap
		@return either the fraction overlap based on the sequence or subsequence scores
		*/
		double fraction_overlap() const noexcept;

		/**
		computes the longest common sequences (possibly more than 1)
		@return a vector of vectors for all of the longest sequences
		*/
		[[nodiscard]] std::vector<std::vector<T>> get_longest_common_sequences() const;

		/**
		finds a longest common subsequence (only 1)
		@return a longest common subsequence
		*/
		[[nodiscard]] std::vector<T> get_a_longest_common_subsequence() const;

		/**
		returns the scoring choice
		@return the sequence scoring enum
		*/
		Scoring get_score_choice() const noexcept;

		/**
		updates the scoring choice
		@param _choice the new choice
		*/
		void set_score_choice(Scoring _choice) noexcept;

		/**
		assembles a greedy chunked longest common sequence
		@return a vector of sequences of T approximating the longest common
		sequences to both documents in the order that they appear in document 1,
		generated through a greedy selection algorithm
		*/
		[[nodiscard]] std::vector< std::vector<T> > get_longest_common_split() const;

	private:
		std::string label; // label for the two documents being compared  
		std::vector<T> doc1, doc2; // two documents 
		Scoring choice; // the choice for scoring 
		size_t tol_window;

		// these members are set/used once the documents are known
		size_t len1, len2; // lengths of the documents, including a null placement 
		size_t sequence_score, subsequence_score, split_score; // longest common sequence/subsequence/sequence split

		std::vector< std::vector<bool> > overlaps; // matrix of where the documents match 
		// allows for computing the sequences/subsequences
		std::vector< std::vector<size_t> > sequence_counts, subsequence_counts, split_sequence_counts;
		double frac; // fraction overlap 
		std::vector<std::tuple<size_t, size_t>> sub_points; // indices of a longest common subsequence 
		std::vector<std::tuple<size_t, size_t, size_t>> seq_start_lengths; // starts and lengths of common sequences
		std::vector<std::tuple<size_t, size_t, size_t>> split_start_lengths; // starts and lengths of split sequences 

		/**
		sets the overlaps matrix
		*/
		void set_overlaps();

		/**
		sets the matrices tracking the longest common (sub)sequences
		*/
		void set_counts();

		/**
		assigns the fraction overlap
		*/
		void set_fraction();

		/**
		sets the sequence count by examining the sequence matrix
		*/
		void set_sequence_counts();

		/**
		sets the subsequence count by examining the subsequence matrix
		*/
		void set_subsequence_counts();

		/**
		sets the split sequence score and establishes the
		beginnings of common sequences in order of appearance in
		document 1
		*/
		void set_split_counts();


		/**
		builds a common subsequence recursively
		@param i the index in document 1
		@param j the index in document 2
		*/
		void backtrack(size_t i, size_t j);


		/**
		uses a greedy method to find the largest common sequence over a range
		@param ilow the lower i-value bound
		@param iup the upper i-value bound
		@param jlow the lower j-value bound
		@param jup the upper j-value bound
		@param len_start a tuple for the length and start  
		*/
		void set_greedy_maxs(size_t ilow, size_t iup, size_t jlow, size_t jup, std::tuple<size_t,size_t,size_t> len_start = {});
		
		std::tuple<size_t,size_t,size_t> tidy(size_t ilow, size_t iup, size_t jlow, size_t jup);


	};

	template<typename T>
	bool operator<(const Sequence_Comps<T>& first, const Sequence_Comps<T>& second) noexcept {
		return first.fraction_overlap() < second.fraction_overlap();
	}

	template<typename T>
	void Sequence_Comps<T>::set_overlaps() {
		for (size_t i = 1; i < len1; ++i) { // iterate over augment doc 1 ("null" at start)
			for (size_t j = 1; j < len2; ++j) { // iterate over augment doc 2 ("null" at start)
				// the minus 1 is due to the offset with the null row/column 
				overlaps[i][j] = (doc1[i - 1] == doc2[j - 1]);
			}
		}
	}

	template<typename T>
	void Sequence_Comps<T>::set_counts() {
		set_sequence_counts(); // direct sequence 
		set_subsequence_counts(); // subsequence
		set_split_counts(); // for the split sequence 
	}

	template<typename T>
	void Sequence_Comps<T>::set_subsequence_counts() {
		for (size_t i = 1; i < len1; ++i) { // start at 1 since will be 0 at index 0 
			for (size_t j = 1; j < len2; ++j) { // start at 1 for same reason 
				if (overlaps[i][j]) { // have a match so one up from previous overlap 
					subsequence_counts[i][j] = 1 + subsequence_counts[i - 1][j - 1];
				}
				else { // take the greater of the paths
					bool i_gtr = subsequence_counts[i - 1][j] > subsequence_counts[i][j - 1];
					subsequence_counts[i][j] = (i_gtr ? subsequence_counts[i - 1][j] :
						subsequence_counts[i][j - 1]
						);
				}
			}
		}
		backtrack(len1 - 1, len2 - 1); // set the longest common subsequence points 
		std::reverse(sub_points.begin(), sub_points.end()); // put in order 
		subsequence_score = subsequence_counts.back().back(); // score at bottom right 		
	}

	template<typename T>
	void Sequence_Comps<T>::set_sequence_counts() {
		for (size_t i = 1; i < len1; ++i) { // start at 1 as index 0 has 0 anyway 
			for (size_t j = 1; j < len2; ++j) { // start at 1 for reason above 
				if (overlaps[i][j]) { // have a match so one up from previous overlap 
					sequence_counts[i][j] = 1 + sequence_counts[i - 1][j - 1];
				}
				// then stays 0
				else {
					sequence_counts[i][j] = 0;
				}
			}
		}
		sequence_score = 0; // set to 0 just in case 
		for (const auto& vec : sequence_counts) { // iterate over the rows 
			for (size_t s : vec) { // look at all values in the row 
				if (sequence_score < s) { // new max 
					sequence_score = s;
				}
			}
		}
		if(sequence_score < tol_window){ // too small to count
			sequence_score = 0;
		}

		// where the maximal sequences begin and their length 
		std::map< std::pair<size_t, size_t>, size_t> beg_lens;
		for (size_t i = 1; i < len1; ++i) { // over all relevant doc 1 indices 
			for (size_t j = 1; j < len2; ++j) { // and for doc 2
				// establish length and beginning position 
				const size_t current_len = sequence_counts[i][j];
				if (current_len>0 && current_len >= tol_window) { // only care if there is reasonable block in common
					beg_lens[std::make_pair(i - (current_len - 1), j - (current_len - 1))] = current_len;
				}
			}
		}

		// now "invert" to order by length 
		std::multimap<size_t, std::pair<size_t, size_t>> len_begs;
		std::set<size_t> lengths; // to store the ordering
		for (const auto& p : beg_lens) { // order by length and beginning 
			len_begs.emplace(std::make_pair(p.second, p.first));
			lengths.insert(p.second);
		}

		// store the beginnings and lengths of maximal sequences 
		seq_start_lengths.clear();
		auto iter = lengths.rbegin(), rend = lengths.rend();
		// loop while long enough and not exhausted lengths 
		for (; iter != rend && *iter >= tol_window; ++iter) {
			auto rng = len_begs.equal_range(*iter); // range of iterators
			for (auto j = rng.first; j != rng.second; ++j) { // j goes over the range
				// j iterates over pairs with key of length and value of the pairing for sequence start 
				seq_start_lengths.emplace_back(j->second.first, j->second.first, j->first);
			}
		}

	}


	template<typename T>
	[[nodiscard]] std::vector< std::vector<T> > Sequence_Comps<T>::get_longest_common_sequences() const {
		std::vector< std::vector<T> > seqs;
		if (sequence_score == 0) { // no overlap means no overlap!
			return seqs;
		}

		for (const auto& t : seq_start_lengths) { // iterate over all tuples
			// index 0 is doc 1 beginning 
			const size_t doc1_start = std::get<0>(t);
			std::vector<T> seq;

			//index 2 is the length
			for (size_t i = 0, len = std::get<2>(t); i < len; ++i) {
				seq.push_back(doc1[doc1_start + i - 1]);
			}

			seqs.push_back(seq);

		}

		std::sort(seqs.begin(), seqs.end());
		auto new_end = std::unique(seqs.begin(), seqs.end());

		return { seqs.begin(), new_end };

	}

	template<typename T>
	std::tuple<size_t,size_t,size_t> Sequence_Comps<T>::tidy(size_t ilow, size_t iup, size_t jlow, size_t jup){
		
		// fix anything that "sticks out"
		for(size_t i=ilow; i <= iup; ++i){ // only iterate over window in i
			for(size_t j=jlow; j<=jup; ++j){ // same for j
				const size_t len = split_sequence_counts[i][j];
			
				if(len==0){ // nothing to fix 
					continue;
				}
			
				// where they originate
				const size_t istart = i - (len - 1);
				const size_t jstart = j - (len - 1);
		
				if(istart < ilow || jstart < jlow){ // start too early
					const size_t loss = 1+(
					(istart<ilow && jstart < jlow)? std::max(ilow-istart,jlow-jstart) 
					: (istart<ilow) ? ilow-istart 
					: jlow-jstart);
					
					split_sequence_counts[i][j] -= loss;
				}
			}
		}
		
		size_t max_seq_score = 0;
		size_t iend = ilow, jend = jlow;
		for (size_t i = ilow; i <= iup; ++i) { // iterate over range of rows  
			for (size_t j = jlow; j <= jup; ++j) { // look at all values in row
			
				if (max_seq_score < split_sequence_counts[i][j]) { // new max					
					max_seq_score = split_sequence_counts[i][j];
					iend = i;
					jend = j;
				}
			}
		}
		
		return std::tuple(iend,jend,max_seq_score);
	}
	
	template<typename T>
	void Sequence_Comps<T>::set_greedy_maxs(size_t ilow, size_t iup, size_t jlow, size_t jup, std::tuple<size_t,size_t,size_t> len_start) {
	

		if(len_start == decltype(len_start){}){ // not computed yet 
			len_start = tidy(ilow,iup, jlow,jup);
		}
		
		auto [iend,jend,max_seq_score] = len_start;
		
		if (max_seq_score<tol_window || max_seq_score==0) { // do nothing when there is nothing
			// zero out range
			for(size_t i=ilow; i <=iup; ++i){
				for(size_t j=jlow; j<=jup; ++j){
					split_sequence_counts[i][j] = 0;
				}
			}
			return;
		}
	
		// where they originate
		const size_t istart = iend - (max_seq_score - 1);
		const size_t jstart = jend - (max_seq_score - 1);

		split_start_lengths.emplace_back(istart, jstart, max_seq_score);
		
		std::tuple<size_t,size_t,size_t> left_up{}, right_up{}, left_down{}, right_down{};
		if (ilow < istart && jlow < jstart) { // still room left and up 
			left_up = tidy(ilow,istart-1,jlow,jstart-1);			
		}
		if (ilow < istart && jend < jup){ // still room right and up
			right_up = tidy(ilow, istart-1, jend+1, jup);
		}
		if (iend < iup && jend < jup) { // still room right and down 
			right_down = tidy(iend + 1, iup, jend + 1, jup);
		}
		if(iend < iup && jlow < jstart){ // still room left and down
			left_down = tidy(iend+1, iup, jlow, jstart-1);
		}
		
		// IMPORTANT: index 2 of tuple is the overlap length!
		
		if(std::get<2>(left_up)+std::get<2>(right_down) > std::get<2>(left_down)+std::get<2>(right_up)){ // better left up and bottom right 
			if(std::get<2>(left_up) > 0){ // worth pursuing
				set_greedy_maxs(ilow,istart-1,jlow,jstart-1,left_up);
			}
			if(std::get<2>(right_down) > 0){ // worth pursuing 
				set_greedy_maxs(iend+1,iup,jend+1,jup,right_down);
			}
		}
		else{ // better left down and upper right 
			if(std::get<2>(left_down) > 0){ // worth pursuing
				set_greedy_maxs(iend+1,iup,jlow,jstart-1,left_down);
			}
			if(std::get<2>(right_up) > 0){ // worth pursuing 
				set_greedy_maxs(ilow,istart-1,jend+1,jup,right_up);
			}			
		}
		
	}

	template<typename T>
	void Sequence_Comps<T>::set_split_counts() {
		split_sequence_counts = sequence_counts; // must start this way
		set_greedy_maxs(0, len1 - 1, 0, len2 - 1);
		split_score = 0;
		for (const auto& t : split_start_lengths) {
			split_score += std::get<2>(t);			
		}
		

		std::sort(split_start_lengths.begin(), split_start_lengths.end(),
			[](const auto& x, const auto& y) {
				// sort by first appearance in document 1
				return std::get<0>(x) < std::get<0>(y);
			});	

	}

	template<typename T>
	void Sequence_Comps<T>::backtrack(size_t i, size_t j) {

		if (i == 0 || j == 0) { // end at this point
			return;
		}

		if (overlaps[i][j]) { // doc1 and 2 overlap at (i,j)
			sub_points.emplace_back(i, j);
			backtrack(i - 1, j - 1);
		}
		// no overlap but go back in doc 1 if that leads to more overlap 
		else if (subsequence_counts[i - 1][j] > subsequence_counts[i][j - 1]) {
			backtrack(i - 1, j);
		}
		else { // go back in doc 2 
			backtrack(i, j - 1);
		}
	}

	template<typename T>
	std::vector<T> Sequence_Comps<T>::get_a_longest_common_subsequence() const {

		std::vector<T> subseq;
		if (subsequence_score == 0) { // no overlap means no overlap!
			return subseq;
		}

		for (const auto& t : sub_points) { // go in order of the points 
			subseq.push_back(doc1[std::get<0>(t) - 1]);
		}

		return subseq;
	}

	template<typename T>
	void Sequence_Comps<T>::set_fraction() {
		const size_t min_len = ((len1 < len2) ? len1 : len2);

		if (min_len == 1) { // no overlap, return early 
			frac = 0;
			return;
		}

		switch (choice) { // three possible choices 
		case Scoring::subsequence:
			frac = static_cast<double>(subsequence_score) / (min_len - 1); break;
		case Scoring::sequence:
			frac = static_cast<double>(sequence_score) / (min_len - 1); break;
		case Scoring::split_sequence:
			frac = static_cast<double>(split_score) / (min_len - 1); break;
		}
	}

	template<typename T>
	Sequence_Comps<T>::Sequence_Comps(std::string _label, const std::vector<T>& _doc1, const std::vector<T>& _doc2, Scoring _choice, size_t _tol_window) :
		label(std::move(_label)),
		doc1(_doc1), doc2(_doc2),
		choice(_choice), tol_window(_tol_window),
		len1(doc1.size() + 1), len2(doc2.size() + 1),
		sequence_score(0), subsequence_score(0), split_score(0),
		overlaps(len1, std::vector<bool>(len2)),
		sequence_counts(len1, std::vector<size_t>(len2)),
		subsequence_counts(len1, std::vector<size_t>(len2)),		
		frac(0)
	{
		set_overlaps();		
		set_counts();
		set_fraction();
	}

	template<typename T>
	const std::string& Sequence_Comps<T>::get_label() const noexcept {
		return label;
	}

	template<typename T>
	size_t Sequence_Comps<T>::size1() const noexcept {
		return len1 - 1;
	}

	template<typename T>
	size_t Sequence_Comps<T>::size2() const noexcept {
		return len2 - 1;
	}

	template<typename T>
	size_t Sequence_Comps<T>::get_subsequence_score() const noexcept {
		return subsequence_score;
	}

	template<typename T>
	size_t Sequence_Comps<T>::get_sequence_score() const noexcept {
		return sequence_score;
	}

	template<typename T>
	size_t Sequence_Comps<T>::get_split_sequence_score() const noexcept {
		return split_score;
	}

	template<typename T>
	double Sequence_Comps<T>::fraction_overlap() const noexcept {
		return frac;
	}



	template<typename T>
	typename Sequence_Comps<T>::Scoring Sequence_Comps<T>::get_score_choice() const noexcept { return choice; }

	template<typename T>
	void Sequence_Comps<T>::set_score_choice(typename Sequence_Comps<T>::Scoring _choice) noexcept {
		choice = _choice;
		set_fraction();
	}

	template<typename T>
	[[nodiscard]] std::vector< std::vector<T> > Sequence_Comps<T>::get_longest_common_split() const {
		std::vector<std::vector<T>> res;
		for (const auto& t : split_start_lengths) { // iterate over (start1,start2,length)-tuples 
			const size_t len = std::get<2>(t);
			if (len >= tol_window) { // must be long enough to include 		
				std::vector<T> split;
				for (size_t i = std::get<0>(t), k = 0; k < len; ++k, ++i) { // include consecutive items 
					split.push_back(doc1[i - 1]);
				}
				res.push_back(std::move(split));
			}
		}
		return res;
	}

}

#endif 
