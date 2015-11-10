#ifndef MOJO_SCANF_FORMAT_SPECIFIERS_H
#define MOJO_SCANF_FORMAT_SPECIFIERS_H

#include <cinttypes>

namespace mojo {

template <typename T>
const char* const scanf_format_specifier(const T&)
{
	return 0;
}

template <>
const char* const scanf_format_specifier(const int16_t&)
{
	return "%" SCNi16;
}

template <>
const char* const scanf_format_specifier(const int32_t&)
{
	return "%" SCNi32;
}

template <>
const char* const scanf_format_specifier(const int64_t&)
{
	return "%" SCNi64;
}

template <>
const char* const scanf_format_specifier(const uint16_t&)
{
	return "%" SCNu16;
}

template <>
const char* const scanf_format_specifier(const uint32_t&)
{
	return "%" SCNu32;
}

template <>
const char* const scanf_format_specifier(const uint64_t&)
{
	return "%" SCNu64;
}

template <>
const char* const scanf_format_specifier(const float&)
{
	return "%f";
}

template <>
const char* const scanf_format_specifier(const double&)
{
	return "%f";
}

} // namespace mojo

#endif // MOJO_SCANF_FORMAT_SPECIFIERS_H
