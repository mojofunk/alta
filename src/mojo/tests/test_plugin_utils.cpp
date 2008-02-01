
#define BOOST_TEST_MODULE mojo_plugin_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/plugin.hpp>
#include <mojo/plugin_ptr.hpp>
#include <mojo/audio_file_plugin.hpp>
#include <mojo/audio_file_plugin_ptr.hpp>
#include <mojo/filesystem_paths.hpp>

#include <mojo/plugin_utils.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

const char* const plugin_path = "build/debug/plugins/AudioFilePlugin/sndfile/libsndfile_audio_file.so";
	
BOOST_AUTO_TEST_CASE( open_plugin_test )
{
	// XXX path needs to be integrated with build etc
	PluginSPtr plug = open_plugin (plugin_path);

	BOOST_REQUIRE(plug);

	BOOST_CHECK_EQUAL(plug->get_author(), "Tim Mayberry");
	BOOST_CHECK_EQUAL(plug->get_description(), "libsndfile plugin");
	BOOST_CHECK_EQUAL(plug->get_version(), "0.0.1");

	PluginSPtr plug_same = open_plugin (plugin_path);

	BOOST_CHECK(plug != plug_same);
}

BOOST_AUTO_TEST_CASE( plugin_typeinfo_test )
{
	PluginSPtr plug = open_plugin (plugin_path);

	BOOST_REQUIRE(plug);

	AudioFilePluginSPtr audio_plugin = boost::dynamic_pointer_cast<AudioFilePlugin>(plug);

	BOOST_CHECK(audio_plugin);
}

void
test_path (const fs::path& p)
{
	BOOST_REQUIRE(!p.empty());
	BOOST_TEST_MESSAGE(p);
}

BOOST_AUTO_TEST_CASE( is_plugin_file_test )
{
	BOOST_REQUIRE(is_plugin_file (plugin_path));
}

BOOST_AUTO_TEST_CASE( plugin_paths_test )
{
	paths_t dirs = plugin_search_path().get_directories();

	for_each (dirs.begin(), dirs.end(), test_path);

	paths_t plugin_files = get_plugin_paths (dirs);

	for_each (plugin_files.begin(), plugin_files.end(), test_path);
}

void
test_plugin (const PluginSPtr& plug)
{
	BOOST_REQUIRE(plug);

	BOOST_TEST_MESSAGE(plug->get_author());
	BOOST_TEST_MESSAGE(plug->get_description());
	BOOST_TEST_MESSAGE(plug->get_version());
}

BOOST_AUTO_TEST_CASE( discover_plugins_test )
{
	PluginSet plugins = discover_plugins (plugin_search_path ());

	for_each (plugins.begin(), plugins.end(), test_plugin);
}
