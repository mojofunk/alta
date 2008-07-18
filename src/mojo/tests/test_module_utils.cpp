
#define BOOST_TEST_MODULE mojo_module_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/audio_file_module.hpp>
#include <mojo/filesystem_paths.hpp>

#include <mojo/module_utils.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

const char* const module_path = "build/debug/modules/AudioFileModule/sndfile/libsndfile_audio_file.so";
	
BOOST_AUTO_TEST_CASE( open_module_test )
{
	// XXX path needs to be integrated with build etc
	ModuleSPtr mod = open_module (module_path);

	BOOST_REQUIRE(mod);

	BOOST_CHECK_EQUAL(mod->get_author(), "Tim Mayberry");
	BOOST_CHECK_EQUAL(mod->get_description(), "libsndfile module");
	BOOST_CHECK_EQUAL(mod->get_version(), "0.0.1");

	ModuleSPtr mod_same = open_module (module_path);

	BOOST_CHECK(mod != mod_same);
}

BOOST_AUTO_TEST_CASE( module_typeinfo_test )
{
	ModuleSPtr mod = open_module (module_path);

	BOOST_REQUIRE(mod);

	AudioFileModuleSPtr audio_module = boost::dynamic_pointer_cast<AudioFileModule>(mod);

	BOOST_CHECK(audio_module);
}

void
test_path (const fs::path& p)
{
	BOOST_REQUIRE(!p.empty());
	BOOST_TEST_MESSAGE(p);
}

BOOST_AUTO_TEST_CASE( is_module_file_test )
{
	BOOST_REQUIRE(is_module_file (module_path));
}

BOOST_AUTO_TEST_CASE( module_paths_test )
{
	paths_t dirs = module_search_path().get_directories();

	for_each (dirs.begin(), dirs.end(), test_path);

	paths_t module_files = get_module_paths (dirs);

	for_each (module_files.begin(), module_files.end(), test_path);
}

void
test_module (const ModuleSPtr& mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());
}

BOOST_AUTO_TEST_CASE( discover_modules_test )
{
	ModuleSet modules = discover_modules (module_search_path ());

	for_each (modules.begin(), modules.end(), test_module);
}
