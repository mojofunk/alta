
#define BOOST_TEST_MODULE mojo_session

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/mojo.hpp>

#include <glibmm/thread.h>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

Project* p1;

class TestBus : public Bus
{
	void on_project_added (Project* p)
	{
		BOOST_TEST_MESSAGE ("project opened");
		p1 = p;
	}

	void on_project_removed (Project* p)
	{
		BOOST_TEST_MESSAGE ("project closed");
		p1 = 0;
	}

	void on_project_saved (Project* p)
	{
		BOOST_TEST_MESSAGE ("project saved");
	}

	void on_track_added (Track* t)
	{
		BOOST_TEST_MESSAGE ("Track Added");
	}

	void on_track_removed (Track* t)
	{
		BOOST_TEST_MESSAGE ("Track Removed");
	}
};

BOOST_AUTO_TEST_CASE( test_session )
{
	Glib::thread_init ();

	Session *s = new Session;
	Bus *bus = new TestBus;

	s->add_bus (bus);

	s->new_project ();

	Project* p2 = p1;

	BOOST_CHECK(p1 == p2);

	TrackOptions opt;

	opt.type = MIDI;
	opt.count = 12;

	s->add_track (opt);

	BOOST_TEST_MESSAGE (p1);
	
	s->close_project (p1);

	s->remove_bus (bus);

	delete s;
	delete bus;
}
