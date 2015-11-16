#ifndef MOJO_PRINTF_FORMAT_SPECIFIERS_H
#define MOJO_PRINTF_FORMAT_SPECIFIERS_H

template <typename T>
const char* const printf_format_specifier(const T&)
{
	return T::PRINTF_FORMAT_SPECIFIER_UNDEFINED
}

template <>
const char* const printf_format_specifier(const int16_t&)
{
	return "%" PRIi16;
}

template <>
const char* const printf_format_specifier(const int32_t&)
{
	return "%" PRIi32;
}

template <>
const char* const printf_format_specifier(const int64_t&)
{
	return "%" PRIi64;
}

template <>
const char* const printf_format_specifier(const uint16_t&)
{
	return "%" PRIu16;
}

template <>
const char* const printf_format_specifier(const uint32_t&)
{
	return "%" PRIu32;
}

template <>
const char* const printf_format_specifier(const uint64_t&)
{
	return "%" PRIu64;
}

template <>
const char* const printf_format_specifier(const float&)
{
	// I think this is the default anyway?
	return "%.6g";
}

template <>
const char* const printf_format_specifier(const double&)
{
	// make sure full precision is retained.
	return "%.12g";
}

#endif // MOJO_PRINTF_FORMAT_SPECIFIERS_H
