#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_string_compose
#endif

#include "test_includes.hpp"

BOOST_AUTO_TEST_CASE(string_compose)
{
	const char* const cstr = "Substitution";
	BOOST_TEST_MESSAGE(compose("Testing const char* %", cstr));

	int i = 123456789;
	BOOST_TEST_MESSAGE(compose("Testing int: %", i));

	bool b = false;
	BOOST_TEST_MESSAGE(compose("Testing bool: %", b));

	BOOST_TEST_MESSAGE(compose("Testing all % % %", cstr, i, b));
}
