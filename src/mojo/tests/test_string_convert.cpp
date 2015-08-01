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

static const double s_test_double = 31459.265359;
static const int s_iter_count = 100000;

namespace {

bool check_au_stream()
{
// There is no point testing another thread on windows with gcc/mingw-w64 as
// check_c_stream seems to not be MT safe
#ifndef MOJO_WINDOWS
	std::ostringstream os;

	BOOST_REQUIRE_NO_THROW(os.imbue(std::locale("en_AU")));
	os << s_test_double;
	bool found_decimal_point = os.str().find('.') != std::string::npos;
	bool found_thousands_comma = os.str().find(',') != std::string::npos;
	return found_decimal_point && found_thousands_comma;
#else
	return true;
#endif
}

bool check_c_stream()
{
	std::ostringstream os;
#ifdef MOJO_WINDOWS
	//std::locale::classic() does not not work with c++03 with gcc/mingw-w64
	//BOOST_REQUIRE_NO_THROW(os.imbue(std::locale("C")));
	BOOST_REQUIRE_NO_THROW(os.imbue(std::locale::classic()));
#else
	BOOST_REQUIRE_NO_THROW(os.imbue(std::locale::classic()));
#endif
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

void* check_au_stream_thread(void*)
{
	for (int n = 0; n < s_iter_count; n++) {
		BOOST_CHECK(check_au_stream());
	}

	return NULL;
}

void* check_c_stream_thread(void*)
{
	for (int n = 0; n < s_iter_count; n++) {
		BOOST_CHECK(check_c_stream());
	}

	return NULL;
}

void* check_fr_printf_thread(void*)
{
	for (int n = 0; n < s_iter_count; n++) {
		BOOST_CHECK(check_fr_printf());
	}

	return NULL;
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
// apple and the test doesn't pass with gcc/mingw-w64 as the test aborts,
// usually with : exception thrown by os.imbue(std::locale::classic())
// TODO: Use std::thread instead of pthreads
BOOST_AUTO_TEST_CASE(imbue_thread_safety)
{
	FrenchLocaleGuard guard;

	std::cerr << "Checking conversions" << std::endl;

	BOOST_CHECK(check_c_stream());
	BOOST_CHECK(check_au_stream());
	BOOST_CHECK(check_fr_printf());

	pthread_t c_stream_thread;
	pthread_t au_stream_thread;
	pthread_t fr_printf_thread;

	std::cerr << "Starting conversion threads" << std::endl;

	BOOST_CHECK(
	    pthread_create(&c_stream_thread, NULL, check_c_stream_thread, NULL) == 0);
	BOOST_CHECK(pthread_create(
	                &au_stream_thread, NULL, check_au_stream_thread, NULL) == 0);
	BOOST_CHECK(pthread_create(
	                &fr_printf_thread, NULL, check_fr_printf_thread, NULL) == 0);

	void* return_value;

	std::cerr << "Joining conversion threads" << std::endl;

	BOOST_CHECK(pthread_join(c_stream_thread, &return_value) == 0);
	BOOST_CHECK(pthread_join(au_stream_thread, &return_value) == 0);
	BOOST_CHECK(pthread_join(fr_printf_thread, &return_value) == 0);
}
