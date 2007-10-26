#define BOOST_TEST_MODULE cformat

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <cformat/cformat.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace cformat;

BOOST_AUTO_TEST_CASE( int32_conversion )
{
	BOOST_CHECK_EQUAL("233141", convert<string>(233141));

	BOOST_CHECK_EQUAL(123456789, convert<int32_t>(string("123456789")));
}

BOOST_AUTO_TEST_CASE( float_conversion )
{

	BOOST_CHECK_CLOSE(0.9876543f, convert<float>(string("0.9876543")),
			std::numeric_limits<float>::epsilon());

	BOOST_CHECK_EQUAL(string("0.987654"), convert<string>(0.987654f));
	BOOST_CHECK_EQUAL(string("103.666"), convert<string>(103.666f));

}
