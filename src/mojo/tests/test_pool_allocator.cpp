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

#include "mojo/core/memory/pool_allocator.hpp"
#include "mojo/core/time/time.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo::memory;

struct Foo
{
	int m_int;
	float m_float;
	double m_double;
};

BOOST_AUTO_TEST_CASE(test_memory_pool_basic)
{
	Pool int_pool(sizeof(int), 128);

	BOOST_CHECK(!int_pool.empty());
}

static const unsigned int num = 128;
static const size_t block_size = sizeof(int);

Pool threaded_int_pool(block_size, num);

boost::lockfree::queue<int*, boost::lockfree::capacity<num>> alloc_queue;

static const int iterations = 10000000;

std::atomic_int alloc_count(0);
std::atomic_int dealloc_count(0);

std::atomic_bool done(false);

std::atomic_bool alloc_is_from_test(true);

void allocate()
{
	while (alloc_count < iterations) {
		int* int_ptr = nullptr;
		int_ptr = (int*)threaded_int_pool.allocate(block_size);

		if (int_ptr == nullptr) {
			continue;
		}

		assert(int_ptr != nullptr);
		++alloc_count;
		while (!alloc_queue.push(int_ptr))
			;

		if (!threaded_int_pool.is_from(int_ptr)) {
			alloc_is_from_test = false;
		}
	}
}

void deallocate()
{
	int* int_alloc = nullptr;
	while (!done) {
		while (alloc_queue.pop(int_alloc)) {
			assert(int_alloc != nullptr);
			threaded_int_pool.deallocate(int_alloc);
			++dealloc_count;
		}
	}

	while (alloc_queue.pop(int_alloc)) {
		assert(int_alloc != nullptr);
		threaded_int_pool.deallocate(int_alloc);
		++dealloc_count;
	}
}

void
test_memory_pool_iteration ()
{
	alloc_count = 0;
	dealloc_count = 0;
	done = false;

	std::thread t1(allocate);
	std::thread t2(allocate);
	std::thread t3(deallocate);
	std::thread t4(deallocate);

	t1.join();
	t2.join();
	done = true;
	t3.join();
	t4.join();

	std::cerr << "alloc_count = " << alloc_count << std::endl;
	std::cerr << "dealloc_count = " << dealloc_count << std::endl;
	BOOST_CHECK(alloc_count == dealloc_count);
	BOOST_CHECK(threaded_int_pool.empty());
}

BOOST_AUTO_TEST_CASE(test_memory_pool_threaded)
{
	for (int i = 0; i < 10; ++i) {
		test_memory_pool_iteration();
	}
}

BOOST_AUTO_TEST_CASE(test_pool_allocator_basic)
{
	PoolAllocator<int> p_small_alloc(128);

	p_small_alloc.empty();

	PoolAllocator<int> p_medium_alloc(256);

	PoolAllocator<Foo> p_large_alloc(512);
}

BOOST_AUTO_TEST_CASE(test_pool_allocator_copy_ctor)
{
	PoolAllocator<int> small_alloc1(256);

	{
		std::vector<int, PoolAllocator<int>> v(small_alloc1);

		for (int i = 0; i < 256; ++i) {
			v.push_back(i);
		}
	}

	// need a test for vector and list
	// list will allocate in single units? while vector will
	// allocate/reallocate in contigious chunks

#if 0
	{
		PoolAllocator<int, 256> small_alloc2(small_alloc1);
	}
#endif
}
