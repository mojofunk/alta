#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_fixed_size_pool
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

BOOST_AUTO_TEST_CASE(test_fixed_size_pool_basic)
{
	FixedSizeObjectPool<int> int_pool(128);

	BOOST_CHECK(!int_pool.empty());
}

static const unsigned int num = 128;

FixedSizeObjectPool<int> threaded_int_pool(num);

boost::lockfree::queue<int*, boost::lockfree::capacity<num>> alloc_queue;

static const int iterations = 10000000;

std::atomic_int alloc_count(0);
std::atomic_int dealloc_count(0);

std::atomic_bool done(false);

std::atomic_bool alloc_is_from_test(true);

void allocate()
{
	while (alloc_count < iterations) {
		int* int_ptr = threaded_int_pool.allocate();

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

void test_memory_pool_iteration()
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
	BOOST_CHECK(threaded_int_pool.available() == num);
}

BOOST_AUTO_TEST_CASE(test_memory_pool_threaded)
{
	for (int i = 0; i < 10; ++i) {
		test_memory_pool_iteration();
	}
}
