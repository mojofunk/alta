#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_module_utils
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <glib.h> //remove this

#include "mojo/core/modules/module_utils.hpp"
#include "mojo/core/filesystem/filesystem_paths.hpp"
#include "mojo/core/string/compose.hpp"

#include "mojo/audio_file/audio_file_module.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

fs::path get_sndfile_module_path()
{
#ifdef MOJO_WINDOWS
	std::string module_name("mojo-audio-file-sndfile");
#else
	std::string module_name("libmojo-audio-file-sndfile");
#endif
	module_name += '.';
	module_name += G_MODULE_SUFFIX;

	fs::path module_path;

	for (auto const& path : module_search_path().get_paths()) {
		if (fs::is_directory(path)) {

			module_path = path / module_name;
			if (fs::exists(module_path)) break;
		}
	}

	BOOST_TEST_MESSAGE(module_path);
	BOOST_CHECK(fs::exists(module_path));

	return module_path;
}

BOOST_AUTO_TEST_CASE(open_module_test)
{
	ModuleSP mod = open_module(get_sndfile_module_path());

	BOOST_REQUIRE(mod);

	BOOST_CHECK_EQUAL(mod->get_author(), "Tim Mayberry");
	BOOST_CHECK_EQUAL(mod->get_description(), "libsndfile module");
	BOOST_CHECK_EQUAL(mod->get_version(), "0.0.1");

	ModuleSP mod_same = open_module(get_sndfile_module_path());

	BOOST_CHECK(mod != mod_same);
}

BOOST_AUTO_TEST_CASE(module_typeinfo_test)
{
	ModuleSP mod = open_module(get_sndfile_module_path());

	BOOST_REQUIRE(mod);

	AudioFileModuleSP audio_module =
	    boost::dynamic_pointer_cast<AudioFileModule>(mod);

	BOOST_CHECK(audio_module);
}

void test_module(const ModuleSP& mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());
}

BOOST_AUTO_TEST_CASE(discover_modules_test)
{
	ModuleSPSet modules = discover_modules(module_search_path());

	for_each(modules.begin(), modules.end(), test_module);
}
