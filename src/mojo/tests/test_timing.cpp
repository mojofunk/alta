#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_timing
#endif

#include "test_includes.hpp"

BOOST_AUTO_TEST_CASE(test_cpp_clocks)
{
	BOOST_TEST_MESSAGE("system_clock");
	BOOST_TEST_MESSAGE(chrono::system_clock::period::num);
	BOOST_TEST_MESSAGE(chrono::system_clock::period::den);
	BOOST_TEST_MESSAGE(chrono::system_clock::is_steady);

	BOOST_TEST_MESSAGE("high_resolution_clock");
	BOOST_TEST_MESSAGE(chrono::high_resolution_clock::period::num);
	BOOST_TEST_MESSAGE(chrono::high_resolution_clock::period::den);
	BOOST_TEST_MESSAGE(chrono::high_resolution_clock::is_steady);

	BOOST_TEST_MESSAGE("steady_clock");
	BOOST_TEST_MESSAGE(chrono::steady_clock::period::num);
	BOOST_TEST_MESSAGE(chrono::steady_clock::period::den);
	BOOST_TEST_MESSAGE(chrono::steady_clock::is_steady);
}

BOOST_AUTO_TEST_CASE(test_timing)
{
	Timing t1;

	BOOST_CHECK(!t1.valid());
	BOOST_CHECK(t1.elapsed() == 0);
	t1.update();
	BOOST_CHECK(t1.valid());
	BOOST_CHECK(t1.elapsed() != 0);
	uint64_t elapsed = t1.elapsed();
	BOOST_CHECK(t1.elapsed() == elapsed);
	BOOST_TEST_MESSAGE(t1.elapsed());
	t1.update();
	BOOST_CHECK(t1.elapsed() != elapsed);
	BOOST_TEST_MESSAGE(t1.elapsed());
}
