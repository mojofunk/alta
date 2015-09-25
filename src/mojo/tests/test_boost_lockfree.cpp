#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_boost_lockfree
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <thread>
#include <atomic>
#include <iostream>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp>

#include "mojo/core/time/time.hpp"

using namespace boost::unit_test;
using namespace boost::lockfree;

BOOST_AUTO_TEST_CASE(test_spsc_queue)
{
	const int count = 100;
	spsc_queue<int, capacity<count>> spsc_queue;
}

const int queue_size = 100;
queue<int, capacity<queue_size>> q;

static std::atomic<int> push_count(0);
static std::atomic<int> pop_count(0);

static std::atomic<bool> done(false);

void produce()
{
	while (!done) {
		int value = ++push_count;
		while (!q.push(value))
			;
	}
}

void consume()
{
	while (!done) {
		int x;
		while (q.pop(x)) {
			++pop_count;
		}
	}

	int x = 0;
	while (q.pop(x)) {
		++pop_count;
	}
}

void
check_push_pop_count ()
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

	done = true;
	t1.join();
	t2.join();
	t3.join();
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
		check_push_pop_count();
	}
}

BOOST_AUTO_TEST_CASE(test_stack)
{
	const int count = 100;
	stack<int, capacity<count>> stack;
}
