#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_core_initializer
#endif

#include "test_includes.hpp"

const int iterations = 1e6;

void init_thread()
{
	for (int i = 0; i < iterations; ++i) {
		core::initialize();
	}
}

void deinit_thread()
{
	for (int i = 0; i < iterations; ++i) {
		core::deinitialize();
	}
}

BOOST_AUTO_TEST_CASE(test_core_initializer)
{
	BOOST_REQUIRE(!core::initialized());

	std::thread init_thread1(init_thread);
	std::thread init_thread2(init_thread);

	init_thread1.join();
	init_thread2.join();

	std::thread deinit_thread1(deinit_thread);
	std::thread deinit_thread2(deinit_thread);

	deinit_thread1.join();
	deinit_thread2.join();

	BOOST_CHECK(!core::initialized());
}
