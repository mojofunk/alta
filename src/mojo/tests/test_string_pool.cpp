#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_string_pool
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/core/string/string_pool.hpp"

using namespace boost::unit_test;
using namespace mojo;

BOOST_AUTO_TEST_CASE(basic_string_pool_test)
{
	StringPool<std::string> string_pool;

	const char* const string_ptr1 = string_pool.emplace_string("Hello World\n");
	const char* const string_ptr2 = string_pool.emplace_string("Hello World\n");

	BOOST_CHECK(string_ptr1 == string_ptr2);

	const char* const string_ptr3 =
	    string_pool.emplace_string(std::string("Hello World\n"));

	BOOST_CHECK(string_ptr2 == string_ptr3);

	std::string tmp = "Hello World\n";

	const char* const string_ptr4 = string_pool.emplace_string(tmp);

	BOOST_CHECK(string_ptr3 == string_ptr4);
}

/*
* Write a TestString class that uses ClassTracker to check that class
* instances aren't being copied etc
*/

BOOST_AUTO_TEST_CASE(test_string_string_pool_test)
{
}
