#define BOOST_TEST_MODULE mojo_string_compose

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "mojo/core/string/compose.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

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
