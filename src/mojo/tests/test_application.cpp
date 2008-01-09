
#define BOOST_TEST_MODULE mojo_application

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/application.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_application )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	{
		ApplicationSPtr app = Application::create (argc, argv);

		BOOST_REQUIRE(app);
		BOOST_REQUIRE(&Application::instance());
	}

	// make sure application instance is invalidated
	BOOST_REQUIRE(!&Application::instance());
}
