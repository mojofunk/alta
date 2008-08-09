
#define BOOST_TEST_MODULE mojo_app

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/mojo.hpp>

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
test_module (const ModuleSPtr& mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());
}

BOOST_AUTO_TEST_CASE( test_get_modules )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);

	BOOST_REQUIRE(app);

	ModuleSet modules = app->get_modules();

	for_each (modules.begin(), modules.end(), test_module);

}
