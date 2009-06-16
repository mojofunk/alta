
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

class TestBus : public SessionBus
{
public:

	TestBus (Session* session) : m_session (session) { }

private:

	void on_project_added (Project* p)
	{
		BOOST_TEST_MESSAGE ("on_project_added");
		Glib::signal_idle().connect(sigc::bind_return(sigc::bind (sigc::mem_fun(*this, &TestBus::project_added), p), false));
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

private:

	void project_added (Project* p)
	{
		BOOST_TEST_MESSAGE ("project_added");
		m_project = p;

		TrackOptions opt;

		opt.type = MIDI;
		opt.count = 12;

		m_session->add_track (p, opt);

		Glib::signal_idle().connect(sigc::bind_return(sigc::bind (sigc::mem_fun(*this, &TestBus::close_project), p), false));
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

	SessionBus *bus = new TestBus(s);

	s->add_bus (bus);

	s->new_project ();

	// need a mainloop here

	s->remove_bus (bus);

	delete s;
	delete bus;
}
