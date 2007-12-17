
#define BOOST_TEST_MODULE ark

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <ark/ark.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace ark;

BOOST_AUTO_TEST_CASE( ark_test )
{
	ark::type_system_init();

	ark::register_type_name (typeid(int), "int");
	ark::register_type_name (typeid(float), "float");
	ark::register_type_name (typeid(std::string), "string");

	BOOST_CHECK(ark::get_type_name (typeid(int)) == "int");
	BOOST_CHECK(ark::get_type_name (typeid(float)) == "float");
	BOOST_CHECK(ark::get_type_name (typeid(std::string)) == "string");
}
