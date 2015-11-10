#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_thread_name_map
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/core/threads/thread_name_map.hpp"

using namespace mojo;

static ThreadNameMap<std::string>& test_thread_map()
{
	static ThreadNameMap<std::string> s_test_thread_map;
	return s_test_thread_map;
}

BOOST_AUTO_TEST_CASE(thread_name_map_basic_test)
{
	BOOST_CHECK(test_thread_map().get_name() ==
	            test_thread_map().unknown_thread_name());

	const std::string thread_name("Basic Test");

	BOOST_CHECK(test_thread_map().insert_name(thread_name));

	BOOST_CHECK(!test_thread_map().insert_name(thread_name));

	BOOST_CHECK(test_thread_map().get_name() == thread_name);

	BOOST_CHECK(test_thread_map().get_name() !=
	            test_thread_map().unknown_thread_name());

	BOOST_CHECK(test_thread_map().erase_name(thread_name));

	BOOST_CHECK(test_thread_map().get_name() ==
	            test_thread_map().unknown_thread_name());
}

static std::atomic<bool> thread_name_map_test_exit(false);

static void thread_name_map_test_do_work()
{
	static std::atomic<int> thread_name_count(0);

	while (!thread_name_map_test_exit) {
		const std::string thread_name =
		    "thread name " + std::to_string(thread_name_count++);
		test_thread_map().insert_name(thread_name);
		// boost test is not thread safe so use assert until figuring out a good
		// way to return test status from thread
		assert(test_thread_map().get_name() == thread_name);
		test_thread_map().erase_name(thread_name);
	}
}

BOOST_AUTO_TEST_CASE(thread_name_map_thread_safety_test)
{
	std::vector<std::thread> test_threads;

	for (int i = 0; i != std::thread::hardware_concurrency() * 2; ++i) {
		test_threads.push_back(std::thread(thread_name_map_test_do_work));
	}

	std::this_thread::sleep_for(std::chrono::seconds(10));

	thread_name_map_test_exit = true;

	for (auto& t : test_threads) {
		BOOST_CHECK_NO_THROW(t.join());
	}
}
