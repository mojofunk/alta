#ifndef CFORMAT_SCANF_FORMAT_INCLUDED
#define CFORMAT_SCANF_FORMAT_INCLUDED

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS 1
#endif

#include <inttypes.h>

namespace cformat {

template <typename T>
const char* const
scanf_format (const T&)
{
	return 0;
}

template <>
const char* const
scanf_format (const int8_t&)
{
	return "%" SCNi8 ;
}

template <>
const char* const
scanf_format (const int16_t&)
{
	return "%" SCNi16;
}

template <>
const char* const
scanf_format (const int32_t&)
{
	return "%" SCNi32;
}

template <>
const char* const
scanf_format (const int64_t&)
{
	return "%" SCNi64;
}

template <>
const char* const
scanf_format (const uint8_t&)
{
	return "%" SCNu8;
}

template <>
const char* const
scanf_format (const uint16_t&)
{
	return "%" SCNu16;
}

template <>
const char* const
scanf_format (const uint32_t&)
{
	return "%" SCNu32;
}

template <>
const char* const
scanf_format (const uint64_t&)
{
	return "%" SCNu64;
}

template <>
const char* const
scanf_format (const float&)
{
	return "%f";
}

template <>
const char* const
scanf_format (const double&)
{
	return "%f";
}

} // namespace cformat

#endif // CFORMAT_SCANF_FORMAT_INCLUDED
