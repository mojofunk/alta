#ifndef CFORMAT_VALUE_TO_STRING_INCLUDED
#define CFORMAT_VALUE_TO_STRING_INCLUDED

#include <string>

#include <cformat/cformat_exception.hpp>
#include <cformat/locale_guard.hpp>
#include <cformat/printf_format.hpp>

namespace cformat {

using std::string;

/**
 * Convert a value to string form using C formatting functions
 *
 * \throw cformat_exception A cformat_exception is thrown if a conversion
 * error occurs.
 *
 * \note A NumericGuard should be used if it is intended that the
 * conversion be the same irrespective of the locale setting.
 */
template <class T>
const string
value_to_string (const T& value)
{
	char buf[32];

	int retval = snprintf (buf, sizeof (buf), printf_format(value), value);

	if(retval <= 0 || retval >= (int)sizeof (buf)) {
		throw cformat_exception();
	}

	return buf;
}

} // namespace cformat


#endif // CFORMAT_VALUE_TO_STRING_INCLUDED
