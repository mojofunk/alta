
#define BOOST_TEST_MODULE mojo

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/type_system.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( mojo_test )
{
	mojo::type_system_init();

	mojo::register_type_name (typeid(int), "int");
	mojo::register_type_name (typeid(float), "float");
	mojo::register_type_name (typeid(std::string), "string");

	BOOST_CHECK(mojo::get_type_name (typeid(int)) == "int");
	BOOST_CHECK(mojo::get_type_name (typeid(float)) == "float");
	BOOST_CHECK(mojo::get_type_name (typeid(std::string)) == "string");
}
