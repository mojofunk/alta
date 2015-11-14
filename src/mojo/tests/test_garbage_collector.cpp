#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_garbage_collector
#endif

#include "test_includes.hpp"

#include <iostream>

const int num_producers = std::thread::hardware_concurrency() * 2;
const int num_gc_threads = 2;

static GarbageCollector gc_basic(1024, num_producers);

static std::atomic<bool> done(false);

static std::atomic<int> test_gc_count(0);

static const int max_instances = 100000;

class TestGC {
public:
	TestGC() { ++test_gc_count; }
	~TestGC() { --test_gc_count; }
};

void test_garbage_collector_basic_producer_thread()
{
	while (!done) {
		// set a max instance count
		while (test_gc_count < max_instances) {
			shared_ptr<TestGC> test_gc_ptr = make_shared<TestGC>();
			assert(test_gc_ptr);

			if (!gc_basic.try_manage(test_gc_ptr)) {
				std::cout << "Producer try_manage failed, GC queue size: "
				          << gc_basic.size_approx() << std::endl;
				gc_basic.manage(test_gc_ptr);
			}
			mojo::usleep(g_random_int_range(1, 20));
			// necessary so that when the gc thread quits join doesn't wait for
			// max_instances to be allocated
			if (done) return;
		}
	}
}

void test_garbage_collector_basic_gc_thread()
{
	cout << "Started GC thread" << endl;
	while (!done) {
		gc_basic.run();
		mojo::usleep(g_random_int_range(1, 20));
	}
}

void test_garbage_collector_basic_iteration()
{
	done = false;

	std::vector<std::thread> basic_producer_threads;
	std::vector<std::thread> basic_gc_threads;

	for (int i = 0; i != num_producers; ++i) {
		basic_producer_threads.push_back(
		    std::thread(test_garbage_collector_basic_producer_thread));
	}

	for (int i = 0; i != num_gc_threads; ++i) {
		basic_gc_threads.push_back(
		    std::thread(test_garbage_collector_basic_gc_thread));
	}

	std::this_thread::sleep_for(std::chrono::seconds(10));

	done = true;

	for (auto& t : basic_producer_threads) {
		BOOST_CHECK_NO_THROW(t.join());
	}

	for (auto& t : basic_gc_threads) {
		BOOST_CHECK_NO_THROW(t.join());
	}

	// There may still be TestGC instances in the GarbageCollector queue
	gc_basic.run();

	BOOST_CHECK(test_gc_count == 0);
}

BOOST_AUTO_TEST_CASE(test_garbage_collector_basic)
{
	for (int i = 0; i < 10; ++i) {
		test_garbage_collector_basic_iteration();
	}
}

BOOST_AUTO_TEST_CASE(test_garbage_collector_try_manage)
{
	// test that no allocation takes place using GC::try_manage

}

BOOST_AUTO_TEST_CASE(test_garbage_collector_run_max_duration)
{
	// test that GC::run_max_duration takes approx time

}
