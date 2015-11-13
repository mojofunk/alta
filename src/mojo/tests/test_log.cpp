#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_log
#endif

#include "test_includes.hpp"

BOOST_AUTO_TEST_CASE(log_simple_test)
{
	mojo::log("NONE", "A Message");
}
