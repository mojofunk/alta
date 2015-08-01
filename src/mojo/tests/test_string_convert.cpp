#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_string_convert
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "mojo/core/string/convert.hpp"

using namespace boost::unit_test;
using namespace std;

#define MAX_INT32_T "2147483647"
#define MIN_INT32_T "-2147483648"

BOOST_AUTO_TEST_CASE(int32_conversion)
{
	string str;
	BOOST_CHECK(mojo::to_string(numeric_limits<int32_t>::max(), str));
	BOOST_CHECK_EQUAL(MAX_INT32_T, str);

	int32_t val = 0;
	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int32_t>::max(), val);

	BOOST_CHECK(mojo::to_string(numeric_limits<int32_t>::min(), str));
	BOOST_CHECK_EQUAL(MIN_INT32_T, str);

	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int32_t>::min(), val);
}

#define MAX_INT64_T "9223372036854775807"
#define MIN_INT64_T "-9223372036854775808"

BOOST_AUTO_TEST_CASE(int64_conversion)
{
	string str;
	BOOST_CHECK(mojo::to_string(numeric_limits<int64_t>::max(), str));
	BOOST_CHECK_EQUAL(MAX_INT64_T, str);

	int64_t val = 0;
	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int64_t>::max(), val);

	BOOST_CHECK(mojo::to_string(numeric_limits<int64_t>::min(), str));
	BOOST_CHECK_EQUAL(MIN_INT64_T, str);

	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int64_t>::min(), val);
}

#ifdef MOJO_WINDOWS
#define MAX_FLOAT "3.40282347e+038"
#define MIN_FLOAT "1.17549435e-038"
#else
#define MAX_FLOAT "3.40282347e+38"
#define MIN_FLOAT "1.17549435e-38"
#endif

BOOST_AUTO_TEST_CASE(float_conversion)
{
	string str;

	BOOST_CHECK(mojo::to_string(numeric_limits<float>::max(), str));
	BOOST_CHECK_EQUAL(MAX_FLOAT, str);

	float val = 0.0f;
	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::max(), val, numeric_limits<float>::epsilon());

	BOOST_CHECK(mojo::to_string(numeric_limits<float>::min(), str));
	BOOST_CHECK_EQUAL(MIN_FLOAT, str);

	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::min(), val, numeric_limits<float>::epsilon());
}

#define MAX_DOUBLE "1.79769313486232e+308"
#define MIN_DOUBLE "2.2250738585072e-308"

BOOST_AUTO_TEST_CASE(double_conversion)
{
	string str;

	BOOST_CHECK(mojo::to_string(numeric_limits<double>::max(), str));

	double val = 0.0f;
	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<double>::max(), val, numeric_limits<double>::epsilon());

	BOOST_CHECK(mojo::to_string(numeric_limits<double>::min(), str));

	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<double>::min(), val, numeric_limits<double>::epsilon());
}

BOOST_AUTO_TEST_CASE(bool_conversion)
{
	string str;

	BOOST_CHECK(mojo::to_string(true, str));
	BOOST_CHECK_EQUAL("true", str);

	bool val = false;
	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_EQUAL(val, true);

	BOOST_CHECK(mojo::to_string(false, str));
	BOOST_CHECK_EQUAL("false", str);

	BOOST_CHECK(mojo::string_to(str, val));
	BOOST_CHECK_EQUAL(val, false);
}
