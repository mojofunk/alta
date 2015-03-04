
#define BOOST_TEST_MODULE mojo_application

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/modules/module.hpp"

#include "mojo/application/application.hpp"

#include "example_application.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_application )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	std::unique_ptr<ExampleApplication> app(new ExampleApplication());

	Application::new_project ();

	Application::iteration (true);

	Application::new_project ();
	Application::new_project ();

	app->close_projects ();
}

void
test_module (const ModuleSP& mod)
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

	ModuleSPSet modules = Application::get_modules();

	for_each (modules.begin(), modules.end(), test_module);
}
