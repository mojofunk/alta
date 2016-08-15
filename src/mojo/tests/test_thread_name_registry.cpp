#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_thread_name_registry
#endif

#include "test_includes.hpp"

static ThreadNameRegistry<std::string>& test_thread_registry()
{
	static ThreadNameRegistry<std::string> s_test_thread_registry;
	return s_test_thread_registry;
}

BOOST_AUTO_TEST_CASE(thread_name_registry_basic_test)
{
	BOOST_CHECK(
	    test_thread_registry().get_thread_name(std::this_thread::get_id()) ==
	    test_thread_registry().unknown_thread_name());

	const std::string thread_name("Basic Test");

	BOOST_CHECK(test_thread_registry().register_thread(thread_name.c_str()));

	BOOST_CHECK(!test_thread_registry().register_thread(thread_name.c_str()));

	BOOST_CHECK(test_thread_registry().get_thread_name(
	                std::this_thread::get_id()) == thread_name);

	BOOST_CHECK(
	    test_thread_registry().get_thread_name(std::this_thread::get_id()) !=
	    test_thread_registry().unknown_thread_name());

	BOOST_CHECK(test_thread_registry().unregister_thread());

	BOOST_CHECK(
	    test_thread_registry().get_thread_name(std::this_thread::get_id()) ==
	    test_thread_registry().unknown_thread_name());
}

static std::atomic<bool> thread_name_registry_test_exit(false);

static void thread_name_registry_test_do_work()
{
	static std::atomic<int> thread_name_count(0);

	while (!thread_name_registry_test_exit) {
		const std::string thread_name =
		    "thread name " + std::to_string(thread_name_count++);
		test_thread_registry().register_thread(thread_name.c_str());
		// boost test is not thread safe so use assert until figuring out a good
		// way to return test status from thread
		assert(test_thread_registry().get_thread_name(std::this_thread::get_id()) ==
		       thread_name);
		test_thread_registry().unregister_thread();
	}
}

BOOST_AUTO_TEST_CASE(thread_name_registry_thread_safety_test)
{
	std::vector<std::thread> test_threads;

	for (int i = 0; i != std::thread::hardware_concurrency() * 2; ++i) {
		test_threads.push_back(std::thread(thread_name_registry_test_do_work));
	}

	std::this_thread::sleep_for(std::chrono::seconds(10));

	thread_name_registry_test_exit = true;

	for (auto& t : test_threads) {
		BOOST_CHECK_NO_THROW(t.join());
	}
}
