
#define BOOST_TEST_MODULE mojo_type_system

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/application.hpp>

#include <mojo/type_system.hpp>
#include <mojo/type_names.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( mojo_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	ApplicationSPtr app = Application::create (argc, argv);

	BOOST_CHECK(mojo::get_type_name (typeid(int)) == int_type_name);
	BOOST_CHECK(mojo::get_type_name (typeid(float)) == float_type_name);
	BOOST_CHECK(mojo::get_type_name (typeid(std::string)) == string_type_name);
}
