#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_core_initializer
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <thread>

#include "mojo/core/init/initialize.hpp"
#include "mojo/core/time/time.hpp"

using namespace mojo;

std::atomic_bool s_exit(false);

void init_thread()
{
	while (!s_exit) {
		for (int i = 0; i < 100; ++i) {
			core::initialize();
		}

		for (int i = 0; i < 100; ++i) {
			core::deinitialize();
		}
	}
}

BOOST_AUTO_TEST_CASE(test_core_initializer)
{
	BOOST_REQUIRE(!core::initialized());

	std::thread thread1(init_thread);
	std::thread thread2(init_thread);

	mojo::sleep(10);

	s_exit = true;

	thread1.join();
	thread2.join();

	BOOST_CHECK(!core::initialized());
}
