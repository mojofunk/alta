#ifndef CFORMAT_STRING_TO_VALUE_INCLUDED
#define CFORMAT_STRING_TO_VALUE_INCLUDED

#include <string>

#include <libcformat/scanf_format.hpp>

namespace cformat {

using std::string;

template <class T>
const T
string_to_value (const string& value_string)
{
	T tmp = 0;

	if(sscanf (value_string.c_str(), scanf_format(tmp), &tmp) != 1) {
		// throw exception?
	}
	return tmp;
}

} // namespace cformat

#endif // CFORMAT_STRING_TO_VALUE_INCLUDED
