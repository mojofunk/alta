#ifndef CFORMAT_PRINTF_FORMAT
#define CFORMAT_PRINTF_FORMAT

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS 1
#endif

#include <inttypes.h>

namespace cformat {

template <typename T>
const char* const
printf_format (const T&)
{
	return 0;
}

template <>
const char* const
printf_format (const int16_t&)
{
	return "%" PRIi16;
}

template <>
const char* const
printf_format (const int32_t&)
{
	return "%" PRIi32;
}

template <>
const char* const
printf_format (const int64_t&)
{
	return "%" PRIi64;
}

template <>
const char* const
printf_format (const uint16_t&)
{
	return "%" PRIu16;
}

template <>
const char* const
printf_format (const uint32_t&)
{
	return "%" PRIu32;
}

template <>
const char* const
printf_format (const uint64_t&)
{
	return "%" PRIu64;
}

template <>
const char* const
printf_format (const float&)
{
	// I think this is the default anyway?
	return "%.6g";
}

template <>
const char* const
printf_format (const double&)
{
	// make sure full precision is retained.
	return "%.12g";
}

} // namespace cformat

#endif // CFORMAT_PRINTF_FORMAT
