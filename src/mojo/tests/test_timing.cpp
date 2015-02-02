#define BOOST_TEST_MODULE mojo_application

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <chrono>

using namespace boost::unit_test;
using namespace std;
//using namespace mojo;

BOOST_AUTO_TEST_CASE( test_clocks )
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
