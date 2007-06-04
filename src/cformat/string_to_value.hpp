#ifndef CFORMAT_STRING_TO_VALUE_INCLUDED
#define CFORMAT_STRING_TO_VALUE_INCLUDED

#include <string>

#include <cformat/cformat_exception.hpp>
#include <cformat/locale_guard.hpp>
#include <cformat/scanf_format.hpp>

namespace cformat {

using std::string;

/**
 * Convert a string to value form using C formatting functions
 *
 * \throw cformat_exception A cformat_exception is thrown if a conversion
 * error occurs.
 *
 * \note A NumericGuard should be used if it is intended that the
 * conversion be the same irrespective of the locale setting.
 */
template <class T>
const T
string_to_value (const string& value_string)
{
	T tmp = 0;

	if(sscanf (value_string.c_str(), scanf_format(tmp), &tmp) != 1) {
		throw cformat_exception();
	}
	return tmp;
}

} // namespace cformat

#endif // CFORMAT_STRING_TO_VALUE_INCLUDED
