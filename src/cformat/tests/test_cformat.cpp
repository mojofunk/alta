#define BOOST_TEST_MODULE cformat

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <cformat/cformat.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace cformat;

#define MAX_INT32_T "2147483647"
#define MIN_INT32_T "-2147483648"

BOOST_AUTO_TEST_CASE( int32_conversion )
{
	BOOST_CHECK_EQUAL(MAX_INT32_T, convert<string>(std::numeric_limits<int32_t>::max()));
	BOOST_CHECK_EQUAL(std::numeric_limits<int32_t>::max(), convert<int32_t>(string(MAX_INT32_T)));
	
	BOOST_CHECK_EQUAL(MIN_INT32_T, convert<string>(std::numeric_limits<int32_t>::min()));
	BOOST_CHECK_EQUAL(std::numeric_limits<int32_t>::min(), convert<int32_t>(string(MIN_INT32_T)));
}

#define MAX_INT64_T "9223372036854775807"
#define MIN_INT64_T "-9223372036854775808"

BOOST_AUTO_TEST_CASE( int64_conversion )
{
	BOOST_CHECK_EQUAL(MAX_INT64_T, convert<string>(std::numeric_limits<int64_t>::max()));
	BOOST_CHECK_EQUAL(std::numeric_limits<int64_t>::max(), convert<int64_t>(string(MAX_INT64_T)));
	
	BOOST_CHECK_EQUAL(MIN_INT64_T, convert<string>(std::numeric_limits<int64_t>::min()));
	BOOST_CHECK_EQUAL(std::numeric_limits<int64_t>::min(), convert<int64_t>(string(MIN_INT64_T)));
}

BOOST_AUTO_TEST_CASE( float_conversion )
{

	BOOST_CHECK_CLOSE(0.9876543f, convert<float>(string("0.9876543")),
			std::numeric_limits<float>::epsilon());

	BOOST_CHECK_EQUAL(string("0.987654"), convert<string>(0.987654f));
	BOOST_CHECK_EQUAL(string("103.666"), convert<string>(103.666f));

}
