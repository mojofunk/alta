#ifndef CFORMAT_INTERPRETER
#define CFORMAT_INTERPRETER

#include <string>

#include <cformat/cformat_exception.hpp>
#include <cformat/printf_format.hpp>

namespace cformat {

template <class TargetType, class SourceType>
class interpreter
{
public:

	TargetType convert (const SourceType& source);

};

/**
 * Partial specialisation for string as target type
 */
template <class SourceType>
class interpreter<std::string, SourceType>
{
public:
	std::string convert (const SourceType& value)
	{
		char buf[32];

		int retval = snprintf (buf, sizeof (buf), printf_format(value), value);

		if(retval <= 0 || retval >= (int)sizeof (buf)) {
			throw cformat_exception();
		}

		return buf;
	}
};

/**
 * Partial specialisation for string as source type
 */
template <class TargetType>
class interpreter<TargetType, std::string>
{
public:
	TargetType convert (const std::string& str)
	{

		TargetType tmp = 0;

		if(sscanf (str.c_str(), scanf_format(tmp), &tmp) != 1) {
			throw cformat_exception();
		}
		return tmp;
	}
};

} // namespace cformat

#endif
