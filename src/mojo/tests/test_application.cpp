
#define BOOST_TEST_MODULE mojo_application

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mutex>

#include "mojo/mojo.hpp"

#include "mojo/interfaces/module.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

class ApplicationListener
{
public:

	void on_project_added (Project* p)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		BOOST_TEST_MESSAGE("Project Added");
		std::set<Project*>::size_type orig_size = m_projects.size ();
		m_projects.insert(p);
		std::set<Project*>::size_type new_size = m_projects.size ();
		BOOST_ASSERT(new_size != orig_size);
	}

	void on_project_removed (Project* p)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		BOOST_TEST_MESSAGE("Project Removed");
		std::set<Project*>::size_type orig_size = m_projects.size ();
		BOOST_ASSERT(orig_size != 0);
		m_projects.erase(p);
		std::set<Project*>::size_type new_size = m_projects.size ();
		BOOST_ASSERT(new_size != orig_size);
	}

	void close_projects ()
	{
		auto i = m_projects.begin();

		while (i != m_projects.end())
		{
			Project* p = *i;
			// erasing will invalidate the iterator so increment now
			i++;
			// this is a sync signal
			Application::close_project (p);
			Application::iteration(true);
		}
	}

private:

	std::set<Project*> m_projects;
	std::mutex         m_mutex;

};

BOOST_AUTO_TEST_CASE( test_application )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	ApplicationListener* listener = new ApplicationListener;

	// connect to project added/removed signals
	Application::connect_project_added (boost::bind (&ApplicationListener::on_project_added, listener, _1));
	Application::connect_project_removed (boost::bind (&ApplicationListener::on_project_removed, listener, _1));

	Application::new_project ();

	Application::iteration (true);

	listener->close_projects ();

	delete listener;
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
