
#ifndef MOJO_STRING_CONVERT_H
#define MOJO_STRING_CONVERT_H

#include <cstdint>
#include <string>
#include <limits>
#include <locale>
#include <sstream>

/**
 * Locale independent string conversion utility functions.
 */
namespace mojo {

template <class T>
bool
string_to (const std::string& str, T& val)
{
	std::istringstream iss(str);
	iss.imbue(std::locale::classic());
	iss >> val;
	return true;
}

template <>
bool
string_to (const std::string& str, bool& val)
{
	if (str.empty())
	{
		return false;
	}
	else if (str == "true")
	{
		val = true;
		return true;
	}
	else if (str == "false")
	{
		val = false;
		return true;
	}
	return false;
}

template <>
bool
string_to (const std::string& str, float& val)
{
	std::istringstream iss(str);
	iss.imbue(std::locale::classic());
	iss >> val;
	return true;
}

template <>
bool
string_to (const std::string& str, double& val)
{
	std::istringstream iss(str);
	iss.imbue(std::locale::classic());
	iss >> val;
	return true;
}

template <class T>
bool
to_string (T val, std::string& str)
{
	std::ostringstream oss;
	oss.imbue(std::locale::classic());
	oss << val;
	str = oss.str();
	return true;
}

template <>
bool
to_string (bool val, std::string& str)
{
	if (val) str = "true";
	else str = "false";
	return true;
}

template <>
bool
to_string (float val, std::string& str)
{
	std::ostringstream oss;
	oss.imbue(std::locale::classic());
	oss.precision(std::numeric_limits<float>::max_digits10);
	oss << val;
	str = oss.str();
	return true;
}


template <>
bool
to_string (double val, std::string& str)
{
	std::ostringstream oss;
	oss.imbue(std::locale::classic());
	oss.precision(std::numeric_limits<double>::max_digits10);
	oss << val;
	str = oss.str();
	return true;
}

} // namespace mojo

#endif // MOJO_STRING_CONVERT_H

