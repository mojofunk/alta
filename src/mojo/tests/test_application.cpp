
#define BOOST_TEST_MODULE mojo_application

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/mojo.hpp"

#include "mojo/interfaces/module.hpp"

#include <glibmm/main.h>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_application )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	BOOST_CHECK_NO_THROW(Application::init (argc, argv));

	Application::new_project ();

	// should receive a project added event for new project

	// loading another project

	// s->load_project (project_file);

	// should receive a project added event for the loaded project

	// need a mainloop here

	Application::cleanup ();
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

	BOOST_CHECK_NO_THROW(Application::init (argc, argv));

	ModuleSPSet modules = Application::get_modules();

	for_each (modules.begin(), modules.end(), test_module);

	Application::cleanup ();
}
