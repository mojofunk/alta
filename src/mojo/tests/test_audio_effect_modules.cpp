
#define BOOST_TEST_MODULE mojo_audio_effect

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/app.hpp>
#include <mojo/audio_effect_module.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void
test_audio_effect_module (AudioEffectModuleSPtr mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());

	std::string api_name;
	mod->get_plugin_api_name (api_name);

	BOOST_TEST_MESSAGE(api_name);

	AudioEffectSPtr ae = mod->open ("fail");

	BOOST_CHECK(!ae);

	if(!ae) return;

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
