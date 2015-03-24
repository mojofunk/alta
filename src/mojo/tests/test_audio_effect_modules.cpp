
#define BOOST_TEST_MODULE mojo_audio_effect

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/application/application.hpp"

#include "mojo/audio_effect/audio_effect.hpp"
#include "mojo/audio_effect/audio_effect_info.hpp"
#include "mojo/audio_effect/audio_effect_parameter_info.hpp"
#include "mojo/audio_effect/audio_effect_module.hpp"


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
test_info (AudioEffectInfoSP info)
{
	BOOST_REQUIRE(info);
	BOOST_MESSAGE(info->get_name ());
	BOOST_MESSAGE(info->get_path ());
}

void
test_parameter_info (const AudioEffectParameterInfo& info)
{
	BOOST_MESSAGE(info.name);
	BOOST_MESSAGE(info.min_value);
	BOOST_MESSAGE(info.max_value);
	BOOST_MESSAGE(info.default_value);
}

void
test_audio_effect (AudioEffectSP aeffect)
{
	BOOST_REQUIRE(aeffect);
	test_info (aeffect->get_info ());

	AudioEffect::ParameterList params = aeffect->get_parameter_list();

	for (const auto& x : params)
	{
		AudioEffectParameterInfo info;
		aeffect->get_parameter_info (x, info);
		test_parameter_info (info);
	}
}

void
test_audio_effect_module (AudioEffectModuleSP mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());
	BOOST_TEST_MESSAGE(mod->get_plugin_api_name ());

	paths_t plugin_dirs = mod->get_plugin_directory_paths ();

	BOOST_CHECK(!plugin_dirs.empty());

	for_each (plugin_dirs.begin(), plugin_dirs.end(), test_path);

	AudioEffectInfoSPSet info = mod->get_plugin_info ();

	for_each (info.begin(), info.end(), test_info);

	for (const auto& x : info)
	{
		AudioEffectSP ae = mod->open (x, 44100);
		test_audio_effect(ae);
	}
}

BOOST_AUTO_TEST_CASE( test_audio_effect_modules )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application::initialize ();
	AudioEffectModuleSPSet modules = Application::get_audio_effect_modules ();

	BOOST_CHECK(!modules.empty());

	for_each (modules.begin(), modules.end(), test_audio_effect_module);
	Application::deinitialize ();
}
