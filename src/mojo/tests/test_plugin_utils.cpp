
#define BOOST_TEST_MODULE mojo_plugin_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/plugin_utils.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( plugin_test )
{
	// XXX needs to be portable, integrated with build etc
	Plugin* plug = open_plugin("build/debug/mojo/plugins/dummy_archive/libdummy_archive.so");

	BOOST_REQUIRE(plug);
	
	BOOST_CHECK_EQUAL(plug->get_author(), "Tim Mayberry");
	BOOST_CHECK_EQUAL(plug->get_description(), "This is a Dummy Plugin for test purposes");
	BOOST_CHECK_EQUAL(plug->get_version(), "0.0.1");

	Plugin* plug_same = open_plugin("build/debug/mojo/plugins/dummy_archive/libdummy_archive.so");

	// same instance should be returned
	BOOST_CHECK_EQUAL(plug, plug_same);

	BOOST_CHECK(close_plugin(plug));

	// plugin should be closed
	BOOST_CHECK(!close_plugin(plug));
	BOOST_CHECK(!close_plugin(plug_same));
}
