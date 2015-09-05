#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/string/compose.hpp"
#include "mojo/core/string/convert.hpp"
#include "mojo/core/debug/debug.hpp"
#endif

MOJO_DEBUG_DOMAIN(STRING_CONVERT);

#define CONVERT_BUF_SIZE 32

namespace mojo {

bool string_to_bool(const std::string& str, bool& val)
{
	if (str.empty()) {
		return false;

	} else if (str == "true") {
		val = true;
		return true;

	} else if (str == "false") {
		val = false;
		return true;
	}
	return false;
}

bool string_to_int32(const std::string& str, int32_t& val)
{
	if (sscanf(str.c_str(), "%" SCNi32, &val) != 1) {
		return false;
	}
	return true;
}

bool string_to_uint32(const std::string& str, uint32_t& val)
{
	if (sscanf(str.c_str(), "%" SCNu32, &val) != 1) {
		return false;
	}
	return true;
}

bool string_to_int64(const std::string& str, int64_t& val)
{
	if (sscanf(str.c_str(), "%" SCNi64, &val) != 1) {
		return false;
	}
	return true;
}

bool string_to_uint64(const std::string& str, uint64_t& val)
{
	if (sscanf(str.c_str(), "%" SCNu64, &val) != 1) {
		return false;
	}
	return true;
}

bool string_to_float(const std::string& str, float& val)
{
	double tmp;
	bool result = string_to_double(str, tmp);
	if (!result) {
		return false;
	}
	val = (float)tmp;
	return true;
}

bool string_to_double(const std::string& str, double& val)
{
	val = g_ascii_strtod(str.c_str(), NULL);
	// TODO can we check for errors in a thread-safe way
	return true;
}

bool bool_to_string(bool val, std::string& str)
{
	if (val)
		str = "true";
	else
		str = "false";
	return true;
}

bool int32_to_string(int32_t val, std::string& str)
{
	char buffer[CONVERT_BUF_SIZE];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIi32, val);

	if (retval <= 0 || retval >= sizeof(buffer)) {
		return false;
	}
	str = buffer;
	return true;
}

bool uint32_to_string(uint32_t val, std::string& str)
{
	char buffer[CONVERT_BUF_SIZE];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIu32, val);

	if (retval <= 0 || retval >= sizeof(buffer)) {
		return false;
	}
	str = buffer;
	return true;
}

bool int64_to_string(int64_t val, std::string& str)
{
	char buffer[CONVERT_BUF_SIZE];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIi64, val);

	if (retval <= 0 || retval >= sizeof(buffer)) {
		return false;
	}
	str = buffer;
	return true;
}

bool uint64_to_string(uint64_t val, std::string& str)
{
	char buffer[CONVERT_BUF_SIZE];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIu64, val);

	if (retval <= 0 || retval >= sizeof(buffer)) {
		return false;
	}
	str = buffer;
	return true;
}

bool float_to_string(float val, std::string& str)
{
	return double_to_string(val, str);
}

bool double_to_string(double val, std::string& str)
{
	char buffer[G_ASCII_DTOSTR_BUF_SIZE];

	str = g_ascii_dtostr(buffer, sizeof(buffer), val);
	// TODO can we check for errors in a thread-safe way
	return true;
}

} // namespace mojo
