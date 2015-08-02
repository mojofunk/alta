#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_string_convert
#endif

#include <thread>

#include <cinttypes>

#include <glib.h>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "mojo/core/string/convert.hpp"

using namespace boost::unit_test;
using namespace std;

#define MAX_INT32_STR "2147483647"
#define MIN_INT32_STR "-2147483648"

BOOST_AUTO_TEST_CASE(int32_conversion)
{
	string str;
	BOOST_CHECK(mojo::int32_to_string(numeric_limits<int32_t>::max(), str));
	BOOST_CHECK_EQUAL(MAX_INT32_STR, str);

	int32_t val = 0;
	BOOST_CHECK(mojo::string_to_int32(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int32_t>::max(), val);

	BOOST_CHECK(mojo::int32_to_string(numeric_limits<int32_t>::min(), str));
	BOOST_CHECK_EQUAL(MIN_INT32_STR, str);

	BOOST_CHECK(mojo::string_to_int32(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int32_t>::min(), val);

	// test the string_to/to_string templates
	int32_t max = numeric_limits<int32_t>::max();
	BOOST_CHECK_EQUAL(max, mojo::string_to<int32_t>(mojo::to_string(max)));

	int32_t min = numeric_limits<int32_t>::min();
	BOOST_CHECK_EQUAL(min, mojo::string_to<int32_t>(mojo::to_string(min)));
}

#define MAX_UINT32_STR "4294967295"
#define MIN_UINT32_STR "0"

BOOST_AUTO_TEST_CASE(uint32_conversion)
{
	string str;
	BOOST_CHECK(mojo::uint32_to_string(numeric_limits<uint32_t>::max(), str));
	BOOST_CHECK_EQUAL(MAX_UINT32_STR, str);

	uint32_t val = 0;
	BOOST_CHECK(mojo::string_to_uint32(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<uint32_t>::max(), val);

	BOOST_CHECK(mojo::uint32_to_string(numeric_limits<uint32_t>::min(), str));
	BOOST_CHECK_EQUAL(MIN_UINT32_STR, str);

	BOOST_CHECK(mojo::string_to_uint32(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<uint32_t>::min(), val);

	// test the string_to/to_string templates
	uint32_t max = numeric_limits<uint32_t>::max();
	BOOST_CHECK_EQUAL(max, mojo::string_to<uint32_t>(mojo::to_string(max)));

	uint32_t min = numeric_limits<uint32_t>::min();
	BOOST_CHECK_EQUAL(min, mojo::string_to<uint32_t>(mojo::to_string(min)));
}

#define MAX_INT64_STR "9223372036854775807"
#define MIN_INT64_STR "-9223372036854775808"

BOOST_AUTO_TEST_CASE(int64_conversion)
{
	string str;
	BOOST_CHECK(mojo::int64_to_string(numeric_limits<int64_t>::max(), str));
	BOOST_CHECK_EQUAL(MAX_INT64_STR, str);

	int64_t val = 0;
	BOOST_CHECK(mojo::string_to_int64(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int64_t>::max(), val);

	BOOST_CHECK(mojo::int64_to_string(numeric_limits<int64_t>::min(), str));
	BOOST_CHECK_EQUAL(MIN_INT64_STR, str);

	BOOST_CHECK(mojo::string_to_int64(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int64_t>::min(), val);

	// test the string_to/to_string templates
	int64_t max = numeric_limits<int64_t>::max();
	BOOST_CHECK_EQUAL(max, mojo::string_to<int64_t>(mojo::to_string(max)));

	int64_t min = numeric_limits<int64_t>::min();
	BOOST_CHECK_EQUAL(min, mojo::string_to<int64_t>(mojo::to_string(min)));
}

#define MAX_FLOAT_WIN "3.4028234663852886e+038"
#define MIN_FLOAT_WIN "1.1754943508222875e-038"
#define MAX_FLOAT_STR "3.4028234663852886e+38"
#define MIN_FLOAT_STR "1.1754943508222875e-38"

BOOST_AUTO_TEST_CASE(float_conversion)
{
	// check float to string and back again for min and max float values
	string str;
	BOOST_CHECK(mojo::float_to_string(numeric_limits<float>::max(), str));
#ifdef MOJO_WINDOWS
	BOOST_CHECK_EQUAL(MAX_FLOAT_WIN, str);
#else
	BOOST_CHECK_EQUAL(MAX_FLOAT_STR, str);
#endif

	float val = 0.0f;
	BOOST_CHECK(mojo::string_to_float(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::max(), val, numeric_limits<float>::epsilon());

	BOOST_CHECK(mojo::float_to_string(numeric_limits<float>::min(), str));
#ifdef MOJO_WINDOWS
	BOOST_CHECK_EQUAL(MIN_FLOAT_WIN, str);
#else
	BOOST_CHECK_EQUAL(MIN_FLOAT_STR, str);
#endif

	BOOST_CHECK(mojo::string_to_float(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::min(), val, numeric_limits<float>::epsilon());

	// test the string_to/to_string templates
	float max = numeric_limits<float>::max();
	BOOST_CHECK_EQUAL(max, mojo::string_to<float>(mojo::to_string(max)));

	float min = numeric_limits<float>::min();
	BOOST_CHECK_EQUAL(min, mojo::string_to<float>(mojo::to_string(min)));

	// check that parsing the windows float string representation with the
	// difference in the exponent part parses correctly on other platforms
	// and vice versa
#ifdef MOJO_WINDOWS
	BOOST_CHECK(mojo::string_to_float(MAX_FLOAT_STR, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::max(), val, numeric_limits<float>::epsilon());

	BOOST_CHECK(mojo::string_to_float(MIN_FLOAT_STR, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::min(), val, numeric_limits<float>::epsilon());
#else
	BOOST_CHECK(mojo::string_to_float(MAX_FLOAT_WIN, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::max(), val, numeric_limits<float>::epsilon());

	BOOST_CHECK(mojo::string_to_float(MIN_FLOAT_WIN, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<float>::min(), val, numeric_limits<float>::epsilon());
#endif
}

#define MAX_DOUBLE_STR "1.7976931348623157e+308"
#define MIN_DOUBLE_STR "2.2250738585072014e-308"

BOOST_AUTO_TEST_CASE(double_conversion)
{
	string str;
	BOOST_CHECK(mojo::double_to_string(numeric_limits<double>::max(), str));
	BOOST_CHECK_EQUAL(MAX_DOUBLE_STR, str);

	double val = 0.0;
	BOOST_CHECK(mojo::string_to_double(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<double>::max(), val, numeric_limits<double>::epsilon());

	BOOST_CHECK(mojo::double_to_string(numeric_limits<double>::min(), str));
	BOOST_CHECK_EQUAL(MIN_DOUBLE_STR, str);

	BOOST_CHECK(mojo::string_to_double(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<double>::min(), val, numeric_limits<double>::epsilon());

	// test the string_to/to_string templates
	double max = numeric_limits<double>::max();
	BOOST_CHECK_EQUAL(max, mojo::string_to<double>(mojo::to_string(max)));

	double min = numeric_limits<double>::min();
	BOOST_CHECK_EQUAL(min, mojo::string_to<double>(mojo::to_string(min)));
}

BOOST_AUTO_TEST_CASE(bool_conversion)
{
	string str;

	// check the normal cases
	BOOST_CHECK(mojo::bool_to_string(true, str));
	BOOST_CHECK_EQUAL("true", str);

	bool val = false;
	BOOST_CHECK(mojo::string_to_bool(str, val));
	BOOST_CHECK_EQUAL(val, true);

	BOOST_CHECK(mojo::bool_to_string(false, str));
	BOOST_CHECK_EQUAL("false", str);

	BOOST_CHECK(mojo::string_to_bool(str, val));
	BOOST_CHECK_EQUAL(val, false);

	BOOST_CHECK(mojo::string_to_bool(str, val));

	// test some junk
	BOOST_CHECK(!mojo::string_to_bool("some junk", val));

	// test the string_to/to_string templates
	BOOST_CHECK_EQUAL(true, mojo::string_to<bool>(mojo::to_string(true)));

	BOOST_CHECK_EQUAL(false, mojo::string_to<bool>(mojo::to_string(false)));
}

static const double s_test_double = 31459.265359;
static const int s_iter_count = 100000;

namespace {

bool check_au_stream()
{
	std::ostringstream os;

	try {
		// This is not a valid locale on Windows but that doesn't matter as
		// this test is not run on Windows as it is known to fail
		os.imbue(std::locale("en_AU"));
	} catch (...) {
		std::cerr << "Unable to imbue stream with en_AU locale" << std::endl;
		return false;
	}

	os << s_test_double;
	bool found_decimal_point = os.str().find('.') != std::string::npos;
	bool found_thousands_comma = os.str().find(',') != std::string::npos;
	return found_decimal_point && found_thousands_comma;
}

bool check_c_stream()
{
	std::ostringstream os;

	try {
		// std::locale::classic() does not not work with c++03 with gcc/mingw-w64
		// but std::locale("C") does
		//os.imbue(std::locale("C"));
		os.imbue(std::locale::classic());
	} catch(...) {
		std::cerr << "Unable to imbue stream with std::locale::classic()" << std::endl;
		return false;
	}
	os << s_test_double;
	return os.str().find('.') != std::string::npos;
}

bool check_fr_printf()
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%.12g", s_test_double);
	bool found = (strchr(buf, ',') != NULL);
	return found;
}

void check_au_stream_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		assert(check_au_stream());
	}
}

void check_c_stream_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		assert(check_c_stream());
	}
}

void check_fr_printf_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		assert(check_fr_printf());
	}
}

// RAII class that sets the global C locale to fr_FR and then resets it
class FrenchLocaleGuard
{
public:

	FrenchLocaleGuard ()
	{
#ifdef MOJO_WINDOWS
		const std::string fr_locale("French_France.1252");
#else
		const std::string fr_locale("fr_FR");
#endif

		m_previous_locale = setlocale(LC_ALL, NULL);

		std::cerr << std::endl;
		std::cerr << "Previous locale was: " << m_previous_locale << std::endl;

		BOOST_CHECK(m_previous_locale != NULL);

		const char* fr_FR_locale = setlocale(LC_ALL, fr_locale.c_str());

		BOOST_CHECK(fr_FR_locale != NULL);

		BOOST_CHECK(fr_locale == fr_FR_locale);

		std::cerr << "Current C locale is: " << fr_locale << std::endl;
	}

	~FrenchLocaleGuard()
	{
		BOOST_CHECK(setlocale(LC_ALL, m_previous_locale) != NULL);
	}

private:

	const char* m_previous_locale;

};

} // anon namespace

// This test is to check that calling std::ios::imbue using a non-global locale
// is thread safe. Apparently it is not on some older gcc versions used by
// apple and the test doesn't pass with gcc/mingw-w64 as the test usually hits
// an assertion as check_fr_printf fails.
#ifndef MOJO_WINDOWS
BOOST_AUTO_TEST_CASE(imbue_thread_safety)
{
	FrenchLocaleGuard guard;

	std::cerr << "Checking conversions" << std::endl;

	BOOST_CHECK(check_c_stream());
	BOOST_CHECK(check_au_stream());
	BOOST_CHECK(check_fr_printf());

	std::cerr << "Starting conversion threads" << std::endl;

	std::thread c_stream_thread(check_c_stream_thread);
	std::thread au_stream_thread(check_au_stream_thread);
	std::thread fr_printf_thread(check_fr_printf_thread);

	std::cerr << "Joining conversion threads" << std::endl;

	c_stream_thread.join();
	au_stream_thread.join();
	fr_printf_thread.join();
}
#endif

namespace {

void check_string_to_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		string str;

		BOOST_CHECK(mojo::double_to_string(numeric_limits<double>::max(), str));

		double val = 0.0;
		BOOST_CHECK(mojo::string_to_double(str, val));
		BOOST_CHECK_CLOSE(
		    numeric_limits<double>::max(), val, numeric_limits<double>::epsilon());

		BOOST_CHECK(mojo::double_to_string(numeric_limits<double>::min(), str));

		BOOST_CHECK(mojo::string_to_double(str, val));
		BOOST_CHECK_CLOSE(
		    numeric_limits<double>::min(), val, numeric_limits<double>::epsilon());
	}
}

} // anon namespace

#ifndef MOJO_WINDOWS
BOOST_AUTO_TEST_CASE(string_to_thread_safety)
{
	FrenchLocaleGuard guard;

	BOOST_CHECK(check_fr_printf());

	std::cerr << "Starting conversion threads" << std::endl;

	std::thread string_to_thread(check_string_to_thread);
	std::thread fr_printf_thread(check_fr_printf_thread);

	std::cerr << "Joining conversion threads" << std::endl;

	string_to_thread.join();
	fr_printf_thread.join();
}
#endif

bool
glib_double_to_string (const double& val, std::string& str)
{
	char buffer[G_ASCII_DTOSTR_BUF_SIZE];

	str = g_ascii_dtostr(buffer, sizeof(buffer), val);
	// TODO can we check for errors in a thread-safe way
	return true;
}

bool
glib_string_to_double (const std::string& str, double& val)
{
	val = g_ascii_strtod(str.c_str(), NULL);
	// TODO can we check for errors in a thread-safe way
	return true;
}

#define GLIB_MAX_DOUBLE_STR "1.7976931348623157e+308"
#define GLIB_MIN_DOUBLE_STR "2.2250738585072014e-308"

namespace {

void
check_glib_double_conversion()
{
	std::string str;

	BOOST_CHECK(glib_double_to_string(numeric_limits<double>::max(), str));
	BOOST_CHECK_EQUAL(GLIB_MAX_DOUBLE_STR, str);

	double val = 0.0;
	BOOST_CHECK(glib_string_to_double(str, val));

	BOOST_CHECK_CLOSE(
		    numeric_limits<double>::max(), val, numeric_limits<double>::epsilon());

	BOOST_CHECK(glib_double_to_string(numeric_limits<double>::min(), str));
	BOOST_CHECK_EQUAL(GLIB_MIN_DOUBLE_STR, str);

	BOOST_CHECK(glib_string_to_double(str, val));
	BOOST_CHECK_CLOSE(
	    numeric_limits<double>::min(), val, numeric_limits<double>::epsilon());
}

} // anon namespace

BOOST_AUTO_TEST_CASE(g_ascii_double_conversion)
{
	FrenchLocaleGuard guard;

	check_glib_double_conversion();
}

namespace {

void check_glib_double_conversion_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		check_glib_double_conversion();
	}
}

} // anon namespace

BOOST_AUTO_TEST_CASE(g_ascii_double_conversion_thread_safety)
{
	FrenchLocaleGuard guard;

	BOOST_CHECK(check_fr_printf());

	std::cerr << "Starting conversion threads" << std::endl;

	std::thread glib_double_conversion_thread(check_glib_double_conversion_thread);
	std::thread fr_printf_thread(check_fr_printf_thread);

	std::cerr << "Joining conversion threads" << std::endl;

	glib_double_conversion_thread.join();
	fr_printf_thread.join();
}

namespace {

bool
int32_to_string (const int32_t& val, std::string& str)
{
	char buffer[32];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIi32, val);

	if (retval <= 0 || retval >= sizeof(buffer)) {
		return false;
	}
	str = buffer;
	return true;
}

bool
string_to_int32 (std::string& str, int32_t& val)
{
	if (sscanf(str.c_str(), "%" SCNi32, &val) != 1) {
		return false;
	}
	return true;
}

void
check_g_snprintf_sscanf_int32_conversion()
{
	// convert int32 to string using snprintf
	string str;
	BOOST_CHECK(int32_to_string(numeric_limits<int32_t>::max(), str));
	BOOST_CHECK_EQUAL(MAX_INT32_STR, str);

	// convert string back to int32 using sscanf and check for equality
	int32_t val = 0;
	BOOST_CHECK(string_to_int32(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int32_t>::max(), val);

	BOOST_CHECK(int32_to_string(numeric_limits<int32_t>::min(), str));
	BOOST_CHECK_EQUAL(MIN_INT32_STR, str);

	BOOST_CHECK(string_to_int32(str, val));
	BOOST_CHECK_EQUAL(numeric_limits<int32_t>::min(), val);
}

void
check_g_snprintf_sscanf_int32_conversion_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		check_g_snprintf_sscanf_int32_conversion();
	}
}

} // anon namespace

BOOST_AUTO_TEST_CASE(g_int32_conversion)
{
	FrenchLocaleGuard guard;

	check_g_snprintf_sscanf_int32_conversion();
}

BOOST_AUTO_TEST_CASE(g_int32_conversion_thread_safety)
{
	// Setting the locale to French should have no impact on the behaviour of
	// printf/sscanf for integers as it should not need to access to the locale
	// but run the tests concurrently anyway to check that it does not.
	FrenchLocaleGuard guard;

	BOOST_CHECK(check_fr_printf());
	check_g_snprintf_sscanf_int32_conversion();

	std::cerr << "Starting conversion threads" << std::endl;

	std::thread g_int32_conversion_thread(
	    check_g_snprintf_sscanf_int32_conversion_thread);
	std::thread fr_printf_thread(check_fr_printf_thread);

	std::cerr << "Joining conversion threads" << std::endl;

	g_int32_conversion_thread.join();
	fr_printf_thread.join();
}

namespace {

bool
check_int_convert ()
{
	int32_t num = g_random_int ();
	return (num == mojo::string_to<int32_t>(mojo::to_string(num)));
}

bool
check_float_convert ()
{
	float num = (float) g_random_double ();
	return (num == mojo::string_to<float>(mojo::to_string(num)));
}

bool
check_double_convert ()
{
	double num = g_random_double ();
	return (num == mojo::string_to<double>(mojo::to_string(num)));
}

void check_int_convert_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		assert(check_int_convert());
	}
}

void check_float_convert_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		assert(check_float_convert());
	}
}

void check_double_convert_thread()
{
	for (int n = 0; n < s_iter_count; n++) {
		assert(check_double_convert());
	}
}

} // anon namespace

BOOST_AUTO_TEST_CASE(convert_thread_safety)
{
	FrenchLocaleGuard guard;

	std::cerr << "Checking conversions" << std::endl;

	BOOST_CHECK(check_int_convert());
	BOOST_CHECK(check_float_convert());
	BOOST_CHECK(check_double_convert());
	BOOST_CHECK(check_fr_printf());

	std::cerr << "Starting conversion threads" << std::endl;

	std::thread convert_int_thread(check_int_convert_thread);
	std::thread convert_float_thread(check_float_convert_thread);
	std::thread convert_double_thread(check_double_convert_thread);
	std::thread fr_printf_thread(check_fr_printf_thread);

	std::cerr << "Joining conversion threads" << std::endl;

	convert_int_thread.join();
	convert_float_thread.join();
	convert_double_thread.join();
	fr_printf_thread.join();
}
