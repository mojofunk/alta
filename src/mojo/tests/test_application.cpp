#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_application
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

#include "example_application.hpp"

BOOST_AUTO_TEST_CASE(test_application)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application::Initializer init;
	std::unique_ptr<ExampleApplication> app(new ExampleApplication());

	Application::new_project();

	Application::iteration(true);

	Application::new_project();
	Application::new_project();

	app->close_projects();
}

void test_application_module(const ModuleSP& mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());
}

BOOST_AUTO_TEST_CASE(test_get_modules)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application::initialize();
	ModuleSPSet modules = Application::get_modules();

	for_each(modules.begin(), modules.end(), test_application_module);
	Application::deinitialize();
}
