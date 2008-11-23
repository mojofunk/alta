
#define BOOST_TEST_MODULE mojo_session

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/mojo.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

class TestBus : public Bus
{
public:

	void on_project_opened (project_t*)
	{
		BOOST_TEST_MESSAGE ("project opened");
	}

	void on_project_closed ()
	{
		BOOST_TEST_MESSAGE ("project closed");
	}

	void on_project_saved ()
	{
		BOOST_TEST_MESSAGE ("project saved");
	}

};

BOOST_AUTO_TEST_CASE( test_session )
{
	Session *s = new Session;
	TestBus *bus = new TestBus;

	s->add_bus (bus);

	s->open_project ("blah");

	s->remove_bus (bus);

	delete s;
}
