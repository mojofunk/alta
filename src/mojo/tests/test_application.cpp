#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_application
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

#include "example_application.hpp"

BOOST_AUTO_TEST_CASE(test_application)
{
	Application app;
	std::unique_ptr<ExampleApplication> example_app(new ExampleApplication());

	Application::new_project();

	Application::iteration(true);

	Application::new_project();
	Application::new_project();

	example_app->close_projects();
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
	Application app;
	ModuleSPSet modules = Application::get_modules();

	for_each(modules.begin(), modules.end(), test_application_module);
}
