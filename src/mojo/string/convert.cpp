#include "convert.hpp"

#include <limits>
#include <locale>
#include <sstream>

namespace {

template <class T>
bool
string_to (const std::string& str, T& val)
{
	std::istringstream iss(str);
	iss.imbue(std::locale::classic());
	iss >> val;
	return true;
}

template <class T>
bool
to_string (T& val, std::string& str)
{
	std::ostringstream oss;
	oss.imbue(std::locale::classic());
	oss << val;
	str = oss.str();
	return true;
}

} // anon

namespace mojo {

bool
string_to_bool (const std::string& str, bool& val)
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

bool string_to_int16 (const std::string& str, int16_t& val)
{
	return string_to<int16_t>(str, val);
}

bool string_to_int32 (const std::string& str, int32_t& val)
{
	return string_to<int32_t>(str, val);
}

bool string_to_int64 (const std::string& str, int64_t& val)
{
	return string_to<int64_t>(str, val);
}

bool string_to_float (const std::string& str, float& val)
{
	std::istringstream iss(str);
	iss.imbue(std::locale::classic());
	iss >> val;
	return true;
}

bool string_to_double (const std::string& str, double& val)
{
	std::istringstream iss(str);
	iss.imbue(std::locale::classic());
	iss >> val;
	return true;
}


bool bool_to_string (bool val, std::string& str)
{
	if (val) str = "true";
	else str = "false";
	return true;
}

bool int16_to_string (int16_t val, std::string& str)
{
	return to_string<int16_t>(val, str);
}

bool int32_to_string (int32_t val, std::string& str)
{
	return to_string<int32_t>(val, str);
}

bool int64_to_string (int64_t val, std::string& str)
{
	return to_string<int64_t>(val, str);
}

bool float_to_string (float val, std::string& str)
{
	std::ostringstream oss;
	oss.imbue(std::locale::classic());
	oss.precision(std::numeric_limits<float>::max_digits10);
	oss << val;
	str = oss.str();
	return true;
}

bool double_to_string (double val, std::string& str)
{
	std::ostringstream oss;
	oss.imbue(std::locale::classic());
	oss.precision(std::numeric_limits<double>::max_digits10);
	oss << val;
	str = oss.str();
	return true;
}

} // namespace mojo
