#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_pool_allocator
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <thread>
#include <atomic>
#include <iostream>

using std::cout;
using std::endl;

#include "mojo/core/memory/fixed_size_pool_allocator.hpp"
#include "mojo/core/time/time.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

struct Foo
{
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