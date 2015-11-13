#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_boost_lockfree
#endif

#include "test_includes.hpp"

#include <iostream>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp>

using namespace boost;

BOOST_AUTO_TEST_CASE(test_spsc_queue)
{
	const int count = 100;
	lockfree::spsc_queue<int, lockfree::capacity<count>> spsc_queue;
}

const int queue_size = 100;
lockfree::queue<int, lockfree::capacity<queue_size>> q;

const int iterations = 10000000;

static std::atomic<int> push_count(0);
static std::atomic<int> pop_count(0);

static std::atomic<bool> done(false);

void produce()
{
	for (int i = 0; i != iterations; ++i) {
		int value = ++push_count;
		while (!q.push(value))
			;
	}
}

void consume()
{
	int value = 0;
	while (!done) {
		while (q.pop(value)) {
			++pop_count;
		}
	}

	while (q.pop(value)) {
		++pop_count;
	}
}

void test_queue_iteration()
{
	done = false;
	push_count = 0;
	pop_count = 0;

	std::thread t1(produce);
	std::thread t2(produce);
	std::thread t3(produce);
	std::thread t4(consume);
	std::thread t5(consume);
	std::thread t6(consume);

	mojo::sleep(5);

	t1.join();
	t2.join();
	t3.join();
	done = true;
	t4.join();
	t5.join();
	t6.join();

	std::cerr << "push_count = " << push_count << std::endl;
	std::cerr << "pop_count = " << pop_count << std::endl;
	BOOST_CHECK(push_count == pop_count);
	BOOST_CHECK(q.empty());
}

BOOST_AUTO_TEST_CASE(test_queue)
{
	BOOST_CHECK(q.is_lock_free());

	for (int i = 0; i < 10; ++i) {
		test_queue_iteration();
	}
}

BOOST_AUTO_TEST_CASE(test_stack)
{
	const int count = 100;
	lockfree::stack<int, lockfree::capacity<count>> stack;
}
