
#define BOOST_TEST_MODULE mojo_plugin_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/plugin.hpp>
#include <mojo/plugin_ptr.hpp>
#include <mojo/plugin_utils.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( plugin_test )
{
	// XXX needs to be portable, integrated with build etc
	PluginSPtr plug = open_plugin("build/debug/plugins/sndfile/libsndfile_audio_file.so");

	BOOST_REQUIRE(plug);

	BOOST_CHECK_EQUAL(plug->get_author(), "Tim Mayberry");
	BOOST_CHECK_EQUAL(plug->get_description(), "libsndfile plugin");
	BOOST_CHECK_EQUAL(plug->get_version(), "0.0.1");

	PluginSPtr plug_same = open_plugin("build/debug/plugins/sndfile/libsndfile_audio_file.so");

	BOOST_CHECK(plug != plug_same);
}
