/**
@file trie.h defines a templated trie data structure that stores sequences
of values with a corresponding mapped value
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/

#ifndef _DATA__TRIE_
#define _DATA__TRIE_

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <optional>
#include <sstream>
#include <algorithm>
#include <type_traits>

namespace data {

	/**
	@class trie serves as a templated trie class where a sequence
	of values is mapped to a value
	@tparam S the type of the sequence
	@tparam M the type being mapped to
	*/
	template<typename S, typename M>
	class trie {
	public:
		/**
		default trie constructor: the fail value will not be set!
		*/
		trie() noexcept;

		/**
		trie constructor
		@param _fail the value to give when a sequence is not found
		*/
		trie(M _fail);

		/**
		copy constructor
		@param other the trie to copy
		*/
		trie(const trie& other);

		/**
		move constructor
		@param other an rvalue
		*/
		trie(trie&& other) noexcept;

		/**
		copy assigment
		@param other a trie to assign from
		*/
		trie& operator=(const trie& other)&;

		/**
		move assignment
		@param other an rvalue to assign from
		*/
		trie& operator=(trie&& other) & noexcept;

		/**
		a swapping member
		@param other another trie to swap with
		*/
		void swap(trie& other) noexcept;

		/**
		destructor must free memory
		*/
		~trie();

		/**
		gives the failure value
		@return the value of fail
		*/
		const M& get_fail_value() const;

		/**
		sets the fail value
		@param _fail the new fail value
		*/
		void set_fail_value(M _fail);

		/**
		inserts a sequence into the trie
		@tparam C the type of the container
		@param c the container
		@param m the value for that sequence
		*/
		template<typename C>
		void insert(C&& c, M val);

		/**
		computes the value for a given sequence
		@tparam C the container type
		@param c the container with the sequence
		@return the value
		*/
		template<typename C>
		const M& get(C&& c) const;

		/**
		@class iterator serves as an input iterator for non-const trie
		*/
		class iterator;

		/**
		@class const_iterator serves as an input iterator for const trie
		*/
		class const_iterator;

		/**
		get iterator to start
		@return begin iterator
		*/
		[[nodiscard]] iterator begin();

		/**
		get iterator to the end
		@return end iterator
		*/
		iterator end() noexcept;

		/**
		get const_iterator to start
		@return a begin iterator
		*/
		[[nodiscard]] const_iterator begin() const;

		/**
		get const_iterator to end
		@return an end iterator
		*/
		const_iterator end() const noexcept;

		/**
		looks for a given sequence
		@tparam C the type of container storing the sequence
		@param c the container
		@return an iterator to that position or past-the-end
		*/
		template<typename C>
		[[nodiscard]] iterator find(C&& c);

		/**
		looks for a given sequence in a const trie
		@tparam C the type of container storing the sequence
		@param c the container
		@return an iterator to that position or past-the-end
		*/
		template<typename C>
		[[nodiscard]] const_iterator find(C&& c) const;

		/**
		erases the mapped value at the current iterator position
		*/
		void erase(iterator pos);
	private:
		/**
		@class node represents a node within the trie,
		storing pointers to other nodes and possibly a value
		*/
		class node;

		using S_node = std::pair<S, node*>;
		using S_const_node = std::pair<S, const node*>;

		node* root;
		M* fail;

	};

	/**
	swaps to tries
	@param first the first
	@param second the second
	*/
	template<typename S, typename M>
	void swap(trie<S, M>& first, trie<S, M>& second) {
		first.swap(second);
	}

	template<typename S, typename M>
	trie<S, M>::trie() noexcept : root(nullptr), fail(nullptr) {}

	template<typename S, typename M>
	trie<S, M>::trie(M _fail) : trie() {
		fail = new M(std::move(_fail));
	}

	/**
	copy constructor
	@param other the trie to copy
	*/
	template<typename S, typename M>
	trie<S, M>::trie(const trie& other) : root(nullptr), fail(nullptr) {
		try { // either could throw an exception 
			root = new node;
			root->copy(other.root);
		}
		catch (...) { // something bad so free things up
			root->self_destruct();
			delete root;
			throw;
		}
		try { // either could throw an exception 
			if (other.fail) {
				fail = new M(*other.fail);
			}
		}
		catch (...) { // something bad so free things up
			delete fail;
			throw;
		}
	}

	/**
	move constructor
	@param other an rvalue
	*/
	template<typename S, typename M>
	trie<S, M>::trie(trie&& other) noexcept : trie() {
		std::swap(root, other.root);
		std::swap(fail, other.fail);
	}

	/**
	copy assigment
	@param other a trie to assign from
	*/
	template<typename S, typename M>
	trie<S, M>& trie<S, M>::operator=(const trie& other)& {
		auto copy{ other };
		swap(other);
		return *this;
	}

	/**
	move assignment
	@param other an rvalue to assign from
	*/
	template<typename S, typename M>
	trie<S, M>& trie<S, M>::operator=(trie&& other) & noexcept {
		trie temp{ std::move(other) };
		swap(temp);
		return *this;
	}

	/**
	a swapping member
	@param other another trie to swap with
	*/
	template<typename S, typename M>
	void trie<S, M>::swap(trie& other) noexcept {
		using std::swap;
		swap(root, other.root);
		swap(fail, other.fail);
	}

	/**
	destructor must free memory
	*/
	template<typename S, typename M>
	trie<S, M>::~trie() {
		if (root) { // if there is a root need to free it up 
			root->self_destruct();
			delete root;
		}
		if (fail) { // had a fail value 
			delete fail;
		}
	}


	template<typename S, typename M>
	const M& trie<S, M>::get_fail_value() const {
		if (fail) { // fail value is set 
			return *fail;
		}
		else { // fail value not set 
			throw std::logic_error("fail value unset");
		}
	}

	template<typename S, typename M>
	void trie<S, M>::set_fail_value(M _fail) {
		if (!fail) { // fail is not set 
			fail = new M(std::move(_fail));
		}
		else { // just write to it 
			*fail = std::move(_fail);
		}
	}

	template<typename S, typename M>
	template<typename C>
	void trie<S, M>::insert(C&& c, M val) {
		if (!root) { // in case root empty, make it
			root = new node;
		}

		node* curr = root;
		for (const auto& e : c) { // for each term
			if (node* n = curr->has(e)) { // if child with value, move to child 
				curr = n;
			}
			else { // set the child and move deeper 
				curr = curr->set(e);
			}
		}
		curr->assign_value(std::move(val));
	}

	template<typename S, typename M>
	template<typename C>
	const M& trie<S, M>::get(C&& c) const {
		const node* curr = root;
		for (const auto& e : c) { // iterate through container 
			if (const node* n = curr->has(e)) { // move to next spot if term found 
				curr = n;
			}
			else { // or return fail if not found 
				return get_fail_value();
			}
		}
		if (curr->mapped) { // now at end so either return mapped value if present 
			return *(curr->mapped);
		}
		else { // or fail value if not 
			return get_fail_value();
		}
	}

	template<typename S, typename M>
	class trie<S, M>::const_iterator {
		friend trie;

		/**
		@class const_trio represents all the information necessary for
		an const_iterator to explore different levels within the trie
		*/
		struct const_trio {
			const node* n; // current node 
			typename std::vector< S_node >::const_iterator curr, end; // position in its nexts and past the end 
			/**
			comparison necessary for comparisons of depths vectors (see below)
			@param left the first const_trio
			@param right the second const_trio
			@return if the two are equal
			*/
			friend bool operator==(const const_trio& left, const const_trio& right) {
				return std::tie(left.n, left.curr, left.end) == std::tie(right.n, right.curr, right.end);
			}
		};

		std::vector<const_trio> depths; // stores position level by level 

		/**
		default constructor, leaves depths empty
		*/
		const_iterator() noexcept;

		/**
		can be given a series of depth positions to start with
		@param _depths the various nodes and vector positions
		*/
		const_iterator(std::vector< const_trio > _depths) noexcept;

		/**
		given a current node and position within that node's nexts,
		this descends the const_iterator as deeply as possible,
		staying at the beginning of each nexts
		*/
		void explore();

		/**
		advances the const_iterator one position forward by attempting to advance to next node
		at current level and exploring deeper or by moving up a level repeatedly until a mapped value is found, possibly stoppingg when depths is empty
		*/
		void advance();

	public:
		/**
		prefix ++, advances const_iterator
		@return advanced const_iterator
		*/
		const_iterator& operator++();

		/**
		suffixed ++, advanced const_iterator
		@return copy of pre-incremented const_iterator
		*/
		const_iterator operator++(int);

		/**
		dereferencing
		@return the mapped value
		*/
		const M& operator*() const;

		/**
		equality comparison
		@param left first const_iterator
		@param right the second const_iterator
		@return if they are the same (have same depths)
		*/
		friend bool operator==(const const_iterator& left, const const_iterator& right) {
			return left.depths == right.depths; // need to keep the definition here 
		}

		/**
		inequality comparison
		@param left first const_iterator
		@param right the second const_iterator
		@return if they have differing depths
		*/
		friend bool operator!=(const const_iterator& left, const const_iterator& right) {
			return !(left == right); // need to keep the definition here 
		}

	};


	template<typename S, typename M>
	class trie<S, M>::iterator {
		friend trie;
		friend const_iterator;

		/**
		@class trio represents all the information necessary for
		an iterator to explore different levels within the trie
		*/
		struct trio {
			node* n; // current node 
			typename std::vector< S_node >::iterator curr, end; // position in its nexts and past the end 
			/**
			comparison necessary for comparisons of depths vectors (see below)
			@param left the first trio
			@param right the second trio
			@return if the two are equal
			*/
			friend bool operator==(const trio& left, const trio& right) {
				return std::tie(left.n, left.curr, left.end) == std::tie(right.n, right.curr, right.end);
			}
		};

		std::vector<trio> depths; // stores position level by level 

		/**
		default constructor, leaves depths empty
		*/
		iterator() noexcept;

		/**
		can be given a series of depth positions to start with
		@param _depths the various nodes and vector positions
		*/
		iterator(std::vector< trio > _depths) noexcept;

		/**
		given a current node and position within that node's nexts,
		this descends the iterator as deeply as possible,
		staying at the beginning of each nexts
		*/
		void explore();

		/**
		advances the iterator one position forward by attempting to advance to next node
		at current level and exploring deeper or by moving up a level repeatedly until a mapped value is found, possibly stoppingg when depths is empty
		*/
		void advance();

	public:
		/**
		prefix ++, advances iterator
		@return advanced iterator
		*/
		iterator& operator++();

		/**
		suffixed ++, advanced iterator
		@return copy of pre-incremented iterator
		*/
		iterator operator++(int);

		/**
		dereferencing
		@return the mapped value
		*/
		M& operator*() const;

		/**
		equality comparison
		@param left first iterator
		@param right the second iterator
		@return if they are the same (have same depths)
		*/
		friend bool operator==(const iterator& left, const iterator& right) {
			return left.depths == right.depths; // need to keep the definition here 
		}

		/**
		inequality comparison
		@param left first iterator
		@param right the second iterator
		@return if they have differing depths
		*/
		friend bool operator!=(const iterator& left, const iterator& right) {
			return !(left == right); // need to keep the definition here 
		}

		/**
		conversion operator
		@return a const_iterator
		*/
		operator const_iterator() const;
	};


	template<typename S, typename M>
	class trie<S, M>::node {
	private:
		friend trie;

		std::vector< S_node > nexts; // nodes that follow with their corresponding sequence term  
		M* mapped; // pointer to the mapped value 

		/**
		default constructor of node is private,
		begins with no other next nodes and no mapped value
		*/
		node() noexcept;

		/**
		used to free the memory: node ensures memory of its subsequent nodes
		is freed up, along with its mapped value (if present)
		*/
		void self_destruct();

		/**
		copies data from one node to another by
		replacing its mapped value (if necessary),
		and replacing the subsequent nodes with new nodes with
		the same data
		@param other the other node to copy from
		*/
		void copy(const node* other);

		/**
		this function looks if the node points to another with a
		given label, const version
		@param s the label
		@return the node with that label or nullptr
		*/
		const node* has(const S& s) const;

		/**
		this function looks if the node points to another with a
		given label, non-const version
		@param s the label
		@return the node with that label or nullptr
		*/
		node* has(const S& s);

		/**
		This function makes a new node neighbour with a given label
		@param s the label for the node's neighbour
		@return a pointer to the newly constructed node
		*/
		node* set(const S& s);

		/**
		This function assigns a mapped value to the node
		@param m the value to take
		*/
		void assign_value(M m);

		/**
		This function gives the mapped value, const version
		@return the pointer to the mapped value, possibly nullptr
		*/
		const M* get_value() const;

		/**
		This function gives the mapped value, non-const version
		@return the pointer to the mapped value, possibly nullptr
		*/
		M* get_value();
	};



	template<typename S, typename M>
	[[nodiscard]] typename trie<S, M>::iterator trie<S, M>::begin() {
		if (!root || root->nexts.empty()) { // nothing 
			return {};
		}

		std::vector< typename iterator::trio > levels;

		typename iterator::trio root_level{ root, root->nexts.begin(), root->nexts.end() };
		levels.push_back(root_level);

		node* n = root;
		while (!n->nexts.empty()) { // keep descending and staying at beginning 		  
			n = levels.back().curr->second; // move down to first available node 

			// since no mapped value, there must be more layers
			typename iterator::trio level{ n, n->nexts.begin(), n->nexts.end() };
			levels.push_back(std::move(level));
		}

		return { levels };
	}

	template<typename S, typename M>
	typename trie<S, M>::iterator trie<S, M>::end() noexcept {
		return {}; // empty is past the end 
	}

	template<typename S, typename M>
	[[nodiscard]] typename trie<S, M>::const_iterator trie<S, M>::begin() const {
		iterator it = const_cast<trie&>(*this).begin();
		return it;
	}

	template<typename S, typename M>
	typename trie<S, M>::const_iterator trie<S, M>::end() const noexcept {
		return {}; // empty is past the end 
	}

	template<typename S, typename M>
	void trie<S, M>::erase(iterator pos) {
		// first free the actual mapped value 
		delete pos.depths.back().n->mapped;
		pos.depths.back().n->mapped = nullptr;

		// until there are valid nexts, keep destructing the nodes 
		size_t i = pos.depths.size() - 1;

		// remove up node by node until we're at the root 
		// or there is a mapped value 
		// or the node has subsequent nodes 
		while (i != 0 && !pos.depths[i].n->mapped && pos.depths[i].n->nexts.empty()) {

			size_t parent = i - 1; // parent 
			// remove child node from parent 
			pos.depths[parent].n->nexts.erase(pos.depths[parent].curr);
			delete pos.depths[i].n;
			--i; // move up 
		}

		// the root will be okay as it never stores a value 
		// and can have an empty nexts 
	}

	template<typename S, typename M>
	template<typename C>
	[[nodiscard]] typename trie<S, M>::iterator trie<S, M>::find(C&& c) {
		std::vector<typename iterator::trio> vec;
		node* curr = root;

		for (const auto& e : c) { // iterate through container 
			if (node* n = curr->has(e)) { // move to next spot if term found
				auto end = curr->nexts.end();
				auto pos = std::find_if(curr->nexts.begin(), curr->nexts.end(),
					[n](const auto& t) { return t.second == n; });
				typename iterator::trio level{ curr,pos,end };
				vec.push_back(std::move(level)); // current node, its current position, and end 
				curr = n;
			}
			else { // or return end if not found 
				return {};
			}
		}

		// extra layer where the mapped value actually is
		auto end = curr->nexts.end();
		auto pos = std::find_if(curr->nexts.begin(), curr->nexts.end(),
			[curr](const auto& t) { return t.second == curr; });
		typename iterator::trio level{ curr,pos,end };
		vec.push_back(std::move(level)); // current node, its current position, and end

		if (curr->mapped) { // now at end so either return mapped value if present

			return { vec };
		}
		else { // or end if not 
			return {};
		}
	}

	template<typename S, typename M>
	template<typename C>
	[[nodiscard]] typename trie<S, M>::const_iterator trie<S, M>::find(C&& c) const {
		return { const_cast<trie&>(*this).find(std::forward<C>(c)) };
	}


	template<typename S, typename M>
	trie<S, M>::iterator::iterator() noexcept {}

	template<typename S, typename M>
	trie<S, M>::iterator::iterator(std::vector< trio > _depths) noexcept : depths(std::move(_depths)) {}

	template<typename S, typename M>
	void trie<S, M>::iterator::explore() {
		node* n = depths.back().curr->second;
		auto& nexts = n->nexts;

		trio level{ n, nexts.begin(), nexts.end() };

		// go deeper 
		depths.push_back(std::move(level));

		if (!nexts.empty()) { // next level has more to explore 
			explore();
		}
	}


	template<typename S, typename M>
	void trie<S, M>::iterator::advance() {
		if (depths.empty()) { // can't do anything here 
			return;
		}

		// anywhere before the last valid spot 
		if (auto next = depths.back().curr, end = depths.back().end; depths.back().curr != end && ++next != end) {
			++depths.back().curr; // move forward and look for value 

			if (!depths.back().n->mapped) { // no value found so go deeper 
				explore();
			}
		}
		else { // last valid spot 
			depths.pop_back();
			if (!depths.empty() && !depths.back().n->mapped) {
				advance();
			}
		}
	}

	template<typename S, typename M>
	typename trie<S, M>::iterator& trie<S, M>::iterator::operator++() {
		advance();
		return *this;
	}

	template<typename S, typename M>
	typename trie<S, M>::iterator trie<S, M>::iterator::operator++(int) {
		auto copy{ *this };
		++(*this);
		return copy;
	}

	template<typename S, typename M>
	M& trie<S, M>::iterator::operator*() const {
		return *depths.back().n->get_value();
	}

	template<typename S, typename M>
	trie<S, M>::iterator::operator typename trie<S, M>::const_iterator() const {
		std::vector<typename const_iterator::const_trio> vec;
		for (const auto& e : depths) { // copy each level to const versions 
			vec.push_back(typename const_iterator::const_trio{ e.n, e.curr, e.end });
		}
		return { vec };
	}

	template<typename S, typename M>
	trie<S, M>::const_iterator::const_iterator() noexcept {}

	template<typename S, typename M>
	trie<S, M>::const_iterator::const_iterator(std::vector< const_trio > _depths) noexcept : depths(std::move(_depths)) {}

	template<typename S, typename M>
	void trie<S, M>::const_iterator::explore() {
		node* n = depths.back().curr->second;
		auto& nexts = n->nexts;

		const_trio level{ n, nexts.begin(), nexts.end() };

		// go deeper 
		depths.push_back(std::move(level));

		if (!nexts.empty()) { // more at next level deeper 
			explore();
		}
	}


	template<typename S, typename M>
	void trie<S, M>::const_iterator::advance() {
		if (depths.empty()) { // can't do anything here 
			return;
		}

		// anywhere before the last valid spot 
		if (auto next = depths.back().curr, end = depths.back().end; depths.back().curr != end && ++next != end) {
			++depths.back().curr; // move forward and look for value 

			if (!depths.back().n->mapped) { // no value found so go deeper 
				explore();
			}
		}
		else { // last valid spot 
			depths.pop_back();
			if (!depths.empty() && !depths.back().n->mapped) {
				advance();
			}
		}
	}

	template<typename S, typename M>
	typename trie<S, M>::const_iterator& trie<S, M>::const_iterator::operator++() {
		advance();
		return *this;
	}

	template<typename S, typename M>
	typename trie<S, M>::const_iterator trie<S, M>::const_iterator::operator++(int) {
		auto copy{ *this };
		++(*this);
		return copy;
	}

	template<typename S, typename M>
	const M& trie<S, M>::const_iterator::operator*() const {
		return *depths.back().n->get_value();
	}


	template<typename S, typename M>
	trie<S, M>::node::node() noexcept : nexts(), mapped(nullptr) {}

	template<typename S, typename M>
	void trie<S, M>::node::self_destruct() {
		for (auto& n : nexts) { // look at all subsequent nodes and destroy 
			n.second->self_destruct();
			delete n.second;
		}
		if (mapped) { // if mapped value, free it up 
			delete mapped;
		}
	}


	template<typename S, typename M>
	void trie<S, M>::node::copy(const node* other) {
		if (!other) { // make sure other is not null 
			return;
		}

		if (other->mapped) { // other stores a value
			if (mapped) { // and currently have mapped value 
				delete mapped;
			}
			mapped = new M(*other->mapped);
		}

		// free up the memory currently held by 
		// the subsequent nodes
		for (const S_node& sn : nexts) {
			delete sn.second;
		}
		nexts.clear(); // start fresh

		if (other->nexts.empty()) { // done already in this case 
			return;
		}

		// first make a "copy" of the sequence values 
		// with a default node 
		size_t i = 0;
		try {
			// iterate over range of other's nexts to make empty nodes 
			for (size_t len = other->nexts.size(); i < len; ++i) {
				S_node temp = std::make_pair(other->nexts[i].first,
					new node);
				nexts.push_back(std::move(temp));
			}
		}
		catch (...) { // failed to allocate perhaps
			for (size_t j = 0; j < i; ++j) { // free up the memory 
				delete nexts[j].second;
				nexts[j].second = nullptr;
			}
			nexts.clear();
			throw; // do not continue since the problems are serious 
		}

		// now set the the connecting nodes 
		for (size_t i = 0, len = nexts.size(); i < len; ++i) {
			nexts[i].second->copy(other->nexts[i].second);
		}
	}


	template<typename S, typename M>
	const typename trie<S, M>::node* trie<S, M>::node::has(const S& s) const {
		auto end = nexts.cend();

		// look among all next values 
		for (auto it = nexts.cbegin(); it != end; ++it) {
			if (it->first == s) { // matching label, give the node 
				return it->second;
			}
		}
		return nullptr;
	}

	template<typename S, typename M>
	typename trie<S, M>::node* trie<S, M>::node::has(const S& s) {
		return const_cast<node*>(const_cast<const node&>(*this).has(s));
	}

	template<typename S, typename M>
	typename trie<S, M>::node* trie<S, M>::node::set(const S& s) {
		node* n = new node;
		nexts.push_back({ s, n });
		return n;
	}

	template<typename S, typename M>
	void trie<S, M>::node::assign_value(M m) {
		if (mapped) { // make sure to free up old value 
			delete mapped;
		}
		mapped = new M(std::move(m));
	}

	template<typename S, typename M>
	const M* trie<S, M>::node::get_value() const {
		return mapped;
	}

	template<typename S, typename M>
	M* trie<S, M>::node::get_value() {
		return mapped;
	}



}

#endif 
