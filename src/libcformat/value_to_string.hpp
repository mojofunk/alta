#ifndef CFORMAT_VALUE_TO_STRING_INCLUDED
#define CFORMAT_VALUE_TO_STRING_INCLUDED

#include <string>

#include <libcformat/printf_format.hpp>

namespace cformat {

using std::string;

template <class T>
const string
value_to_string (const T& value)
{
	char buf[32];
	int retval = snprintf (buf, sizeof (buf), printf_format(value), value);

	if(retval <= 0 || retval >= sizeof (buf)) {
		// throw exception?
	}

	return buf;
}

} // namespace cformat


#endif // CFORMAT_VALUE_TO_STRING_INCLUDED
