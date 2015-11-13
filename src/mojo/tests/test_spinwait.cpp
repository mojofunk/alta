#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE spinwait
#endif

#include "test_includes.hpp"

BOOST_AUTO_TEST_CASE(test_spinwait)
{
	mojo::Timing timer;

	mojo::spinwait(100);
	timer.update();
	BOOST_CHECK(timer.elapsed() > 100);

	timer.start();
	mojo::spinwait(10000);
	timer.update();
	BOOST_CHECK(timer.elapsed() > 10000);

	timer.start();
	mojo::spinwait(1000000);
	timer.update();
	BOOST_CHECK(timer.elapsed() > 1000000);
}
