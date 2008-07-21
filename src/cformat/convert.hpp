#ifndef CFORMAT_CONVERT
#define CFORMAT_CONVERT

#include <cformat/interpreter.hpp>

namespace cformat {

using std::string;

/**
 * Convert from one type to another using C formatting functions
 * where either the source type or target type is a std::string
 *
 * \throw cformat_exception A cformat_exception is thrown if a conversion
 * error occurs.
 */
template <class TargetType, class SourceType>
TargetType
convert (const SourceType& value)
{
	interpreter<TargetType, SourceType> i;

	return i.convert(value);
}

} // namespace cformat

#endif // CFORMAT_CONVERT
