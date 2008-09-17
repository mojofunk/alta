
#define BOOST_TEST_MODULE mojo_module_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <mojo/mojo.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

const char* const module_path = "build/debug/modules/AudioFileModule/sndfile/libsndfile_audio_file.so";
	
BOOST_AUTO_TEST_CASE( open_module_test )
{
	// XXX path needs to be integrated with build etc
	ModuleSP mod = open_module (module_path);

	BOOST_REQUIRE(mod);

	BOOST_CHECK_EQUAL(mod->get_author(), "Tim Mayberry");
	BOOST_CHECK_EQUAL(mod->get_description(), "libsndfile module");
	BOOST_CHECK_EQUAL(mod->get_version(), "0.0.1");

	ModuleSP mod_same = open_module (module_path);

	BOOST_CHECK(mod != mod_same);
}

BOOST_AUTO_TEST_CASE( module_typeinfo_test )
{
	ModuleSP mod = open_module (module_path);

	BOOST_REQUIRE(mod);

	AudioFileModuleSP audio_module = boost::dynamic_pointer_cast<AudioFileModule>(mod);

	BOOST_CHECK(audio_module);
}

void
test_path (const fs::path& p)
{
	BOOST_REQUIRE(!p.empty());
	BOOST_TEST_MESSAGE(p);
}

void
test_module (const ModuleSP& mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());
}

BOOST_AUTO_TEST_CASE( discover_modules_test )
{
	ModuleSPSet modules = discover_modules (module_search_path ());

	for_each (modules.begin(), modules.end(), test_module);
}
