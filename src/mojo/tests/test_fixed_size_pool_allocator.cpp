#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_pool_allocator
#endif

#include "test_includes.hpp"

#include <iostream>

using std::cout;
using std::endl;

struct Foo {
	int m_int;
	float m_float;
	double m_double;
};

BOOST_AUTO_TEST_CASE(test_pool_allocator_basic)
{
	FixedSizePoolAllocator<int> p_small_alloc(128);

	p_small_alloc.empty();

	FixedSizePoolAllocator<int> p_medium_alloc(256);

	FixedSizePoolAllocator<Foo> p_large_alloc(512);
}

BOOST_AUTO_TEST_CASE(test_pool_allocator_copy_ctor)
{
	FixedSizePoolAllocator<int> small_alloc1(256);

	{
		std::vector<int, FixedSizePoolAllocator<int>> v(small_alloc1);

		for (int i = 0; i < 256; ++i) {
			v.push_back(i);
		}
	}

// need a test for vector and list
// list will allocate in single units? while vector will
// allocate/reallocate in contigious chunks

#if 0
	{
		FixedSizePoolAllocator<int, 256> small_alloc2(small_alloc1);
	}
#endif
}

#if 0

// doesn't work as allocator doesn't have default ctor
typedef std::basic_string<char,
                          std::char_traits<char>,
                          FixedSizePoolAllocator<char>> PoolTestString;

BOOST_AUTO_TEST_CASE(test_pool_allocator_string)
{
	FixedSizePoolAllocator<char> small_alloc1(256);

	PoolTestString pool_string(small_alloc1);

}
#endif
