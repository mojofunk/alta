
#define BOOST_TEST_MODULE mojo_app

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/app.hpp>
#include <mojo/plugin.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_init )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	{
		AppSPtr app = App::init (argc, argv);

		BOOST_REQUIRE(app);
	}
}

void
test_plugin (const PluginSPtr& plug)
{
	BOOST_REQUIRE(plug);

	BOOST_TEST_MESSAGE(plug->get_author());
	BOOST_TEST_MESSAGE(plug->get_description());
	BOOST_TEST_MESSAGE(plug->get_version());
}

BOOST_AUTO_TEST_CASE( test_get_plugins )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);

	BOOST_REQUIRE(app);

	PluginSet plugins = app->get_plugins();

	for_each (plugins.begin(), plugins.end(), test_plugin);

}
