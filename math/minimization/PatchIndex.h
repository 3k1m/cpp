/**
For C++ compilers that do not have index_sequence this
is a patch. The index_sequence was introduced in C++14 and
beyond
*/

#ifndef _PATCHES__INDEX_
#define _PATCHES__INDEX_

namespace patch {

	template <std::size_t... Is>
	struct index_sequence {
		virtual ~index_sequence() {}
	};

	template <std::size_t N, std::size_t... Is>
	struct build_index_sequence
		: build_index_sequence<N - 1, N - 1, Is...> {};

	template <std::size_t... Is>
	struct build_index_sequence<0, Is...> : index_sequence<Is...> {};

}

#endif
