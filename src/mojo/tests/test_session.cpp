
#define BOOST_TEST_MODULE mojo_session

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/mojo.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

mojo::project_t p1;

class TestBus : public Bus
{
	void on_project_added (project_t p)
	{
		BOOST_TEST_MESSAGE ("project opened");
		p1 = p;
	}

	void on_project_removed (project_t p)
	{
		BOOST_TEST_MESSAGE ("project closed");
		p1.reset ();
	}

	void on_project_saved ()
	{
		BOOST_TEST_MESSAGE ("project saved");
	}
};

BOOST_AUTO_TEST_CASE( test_session )
{
	Session *s = new Session;
	Bus *bus = new TestBus;

	s->add_bus (bus);

	s->new_project ();

	project_t p2 = p1;

	BOOST_CHECK(p1 == p2);

	s->close_project (p1);

	s->remove_bus (bus);

	delete s;
}
