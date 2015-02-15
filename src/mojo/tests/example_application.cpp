#include "example_application.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

ExampleApplication::ExampleApplication()
{
	BOOST_TEST_MESSAGE("ExampleApplication: ExampleApplication()");
	// connect to project added/removed signals
	Application::connect_project_added (boost::bind (&ExampleApplication::on_project_added, this, _1));
	Application::connect_project_removed (boost::bind (&ExampleApplication::on_project_removed, this, _1));
}

ExampleApplication::~ExampleApplication()
{
	BOOST_TEST_MESSAGE("ExampleApplication: ~ExampleApplication()");
}

void
ExampleApplication::on_project_added (Project* p)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	BOOST_TEST_MESSAGE("ExampleApplication: Project Added");
	std::set<Project*>::size_type orig_size = m_projects.size ();
	m_projects.insert(p);
	std::set<Project*>::size_type new_size = m_projects.size ();
	BOOST_ASSERT(new_size != orig_size);
}

void
ExampleApplication::on_project_removed (Project* p)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	BOOST_TEST_MESSAGE("ExampleApplication: Project Removed");
	std::set<Project*>::size_type orig_size = m_projects.size ();
	BOOST_ASSERT(orig_size != 0);
	m_projects.erase(p);
	std::set<Project*>::size_type new_size = m_projects.size ();
	BOOST_ASSERT(new_size != orig_size);
}

void
ExampleApplication::close_projects ()
{
	auto i = m_projects.begin();

	while (i != m_projects.end())
	{
		Project* p = *i;
		BOOST_TEST_MESSAGE("ExampleApplication: close_projects");
		// this is a sync signal
		Application::close_project (p);
		Application::iteration(true);
		i = m_projects.begin();
	}
}
