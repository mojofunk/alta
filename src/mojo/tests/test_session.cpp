
#define BOOST_TEST_MODULE mojo_session

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/mojo.hpp>

#include <glibmm/thread.h>
#include <glibmm/main.h>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

class TestSessionEventHandler : public SessionEventHandler
{
public:

	TestSessionEventHandler (Session* session) : m_session (session) { }

private:

	void on_project_added (Project* p)
	{
		BOOST_TEST_MESSAGE ("on_project_added");
		Glib::signal_idle().connect(sigc::bind_return(sigc::bind (sigc::mem_fun(*this, &TestSessionEventHandler::project_added), p), false));
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

		m_session->add_track (p, opt);

		Glib::signal_idle().connect(sigc::bind_return(sigc::bind (sigc::mem_fun(*this, &TestSessionEventHandler::close_project), p), false));
	}

	void close_project (Project* p)
	{
		BOOST_TEST_MESSAGE ("close_project");
		m_session->close_project (m_project);
	}

	Session* m_session;

	Project* m_project;
	Track* m_track;

};

BOOST_AUTO_TEST_CASE( test_session )
{
	Glib::thread_init ();

	Session *s = new Session;

	SessionEventHandler *handler = new TestSessionEventHandler(s);

	s->add_event_handler (handler);
	//s->connect_event_handler (handler, SessionEvent::ProjectAdded);
	//s->connect_event_handler (handler, SessionEvent::ProjectRemoved);
	//s->connect_event_handler (handler, SessionEvent::TracksAdded);
	//s->connect_event_handler (handler, SessionEvent::TracksRemoved);
	//s->connect_event_handler (handler, TransportEvent::SpeedChanged);
	//s->connect_event_handler (handler, TransportEvent::PositionChanged);
	//s->connect_event_handler (handler, TransportEvent::RecordEnabledChanged);
	// handler->unref (); ??


	s->new_project ();

	// should receive a project added event for new project



	// loading another project

	//s->load_project (project_file);

	// should receive a project added event for the loaded project

	// need a mainloop here

	s->remove_event_handler (handler);

	//s->remove_event_handler (handler); //disconnects all event signals

	delete s;
	delete handler;
}
