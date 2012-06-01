
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

class TestApplicationEventHandler : public ApplicationEventHandler
{
private:

	void on_project_added (Project* p)
	{
		BOOST_TEST_MESSAGE ("on_project_added");
		Glib::signal_idle().connect(sigc::bind_return(sigc::bind (sigc::mem_fun(*this, &TestApplicationEventHandler::project_added), p), false));
	}

	void on_project_removed (Project* p)
	{
		BOOST_TEST_MESSAGE ("project closed");
	}

	void on_project_saved (Project* p)
	{
		BOOST_TEST_MESSAGE ("project saved");
	}

	void on_track_added (Project*, Track* t)
	{
		BOOST_TEST_MESSAGE ("Track Added");
	}

	void on_track_removed (Project*, Track* t)
	{
		BOOST_TEST_MESSAGE ("Track Removed");
	}

	void on_project_property_changed (Project*, Property* )
	{
		BOOST_TEST_MESSAGE ("Project Property Changed");
	}

	void on_active_project_changed (Project*)
	{
		BOOST_TEST_MESSAGE ("Active Project Changed");
	}

	void on_track_property_changed (Project*, Track*, Property*)
	{
		BOOST_TEST_MESSAGE ("Track Property Changed");
	}

	void on_transport_speed_changed (Project*, float speed)
	{
		BOOST_TEST_MESSAGE ("Transport Speed Changed");
	}

	void on_transport_position_changed (Project*, count_t)
	{
		BOOST_TEST_MESSAGE ("Transport Position Changed");
	}

	void on_transport_record_changed (Project*, bool)
	{
		BOOST_TEST_MESSAGE ("Transport Record Changed");
	}

private:

	void project_added (Project* p)
	{
		BOOST_TEST_MESSAGE ("project_added");
		m_project = p;

		TrackOptions opt;

		opt.type = MIDI;
		opt.count = 12;

		Application::add_track (p, opt);

		Glib::signal_idle().connect(sigc::bind_return(sigc::bind (sigc::mem_fun(*this, &TestApplicationEventHandler::close_project), p), false));
	}

	void close_project (Project* p)
	{
		BOOST_TEST_MESSAGE ("close_project");
		Application::close_project (m_project);
	}

	Project* m_project;
	Track* m_track;

};

BOOST_AUTO_TEST_CASE( test_application )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	BOOST_CHECK_NO_THROW(Application::init (argc, argv));

	ApplicationEventHandler *handler = new TestApplicationEventHandler();

	BOOST_REQUIRE(handler);

	Application::add_event_handler (handler);
	//s->connect_event_handler (handler, ApplicationEvent::ProjectAdded);
	//s->connect_event_handler (handler, ApplicationEvent::ProjectRemoved);
	//s->connect_event_handler (handler, ApplicationEvent::TracksAdded);
	//s->connect_event_handler (handler, ApplicationEvent::TracksRemoved);
	//s->connect_event_handler (handler, TransportEvent::SpeedChanged);
	//s->connect_event_handler (handler, TransportEvent::PositionChanged);
	//s->connect_event_handler (handler, TransportEvent::RecordEnabledChanged);
	// handler->unref (); ??


	Application::new_project ();

	// should receive a project added event for new project



	// loading another project

	//s->load_project (project_file);

	// should receive a project added event for the loaded project

	// need a mainloop here

	Application::remove_event_handler (handler);

	delete handler;

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
