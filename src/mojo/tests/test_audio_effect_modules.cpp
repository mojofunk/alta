
#define BOOST_TEST_MODULE mojo_audio_effect

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/app.hpp>
#include <mojo/audio_effect.hpp>
#include <mojo/audio_effect_module.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void
test_path (const fs::path& path)
{
	BOOST_REQUIRE(!path.empty());
	BOOST_TEST_MESSAGE(path.string());
}

void
test_audio_effect (AudioEffectSPtr aeffect)
{
	BOOST_CHECK(aeffect);

	if(aeffect)
	{
		BOOST_TEST_MESSAGE(aeffect->get_name());
	}
}

void
test_audio_effect_module (AudioEffectModuleSPtr mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());
	BOOST_TEST_MESSAGE(mod->get_plugin_api_name ());

	paths_t plugin_dirs = mod->get_plugin_directory_paths ();

	BOOST_CHECK(!plugin_dirs.empty());

	for_each (plugin_dirs.begin(), plugin_dirs.end(), test_path);

	paths_t plugin_paths = mod->get_plugin_paths ();

	for_each (plugin_paths.begin(), plugin_paths.end(), test_path);

	for (paths_t::const_iterator i = plugin_paths.begin ();
		       	i != plugin_paths.end(); ++i)
	{
		AudioEffectSPtr ae = mod->open (*i); 
		test_audio_effect(ae);
	}
}

BOOST_AUTO_TEST_CASE( test_audio_effect_modules )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);
	BOOST_REQUIRE(app);

	AudioEffectModuleSet modules = App::get_audio_effect_modules ();

	BOOST_CHECK(!modules.empty());

	for_each (modules.begin(), modules.end(), test_audio_effect_module);
}
