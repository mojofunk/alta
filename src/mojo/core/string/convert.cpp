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
	}
	if (g_ascii_strncasecmp(str.c_str(), "true", str.length()) == 0) {
		val = true;
		return true;

	} else if (g_ascii_strncasecmp(str.c_str(), "false", str.length()) == 0) {
		val = false;
		return true;

	} else if (str == "1") {
		val = true;
		return true;

	} else if (str == "0") {
		val = false;
		return true;

	} else if (str == "y") {
		val = true;
		return true;

	} else if (str == "n") {
		val = false;
		return true;

	} else if (g_ascii_strncasecmp(str.c_str(), "yes", str.length()) == 0) {
		val = true;
		return true;

	} else if (g_ascii_strncasecmp(str.c_str(), "no", str.length()) == 0) {
		val = false;
		return true;
	}

	MOJO_DEBUG_MSG(STRING_CONVERT,
	               compose("string_to_bool conversion failed for %", str));

	return false;
}

bool string_to_int16(const std::string& str, int16_t& val)
{
	if (sscanf(str.c_str(), "%" SCNi16, &val) != 1) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("string_to_int16 conversion failed for %", str));
		return false;
	}
	return true;
}

bool string_to_uint16(const std::string& str, uint16_t& val)
{
	if (sscanf(str.c_str(), "%" SCNu16, &val) != 1) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("string_to_uint16 conversion failed for %", str));
		return false;
	}
	return true;
}

bool string_to_int32(const std::string& str, int32_t& val)
{
	if (sscanf(str.c_str(), "%" SCNi32, &val) != 1) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("string_to_int32 conversion failed for %", str));
		return false;
	}
	return true;
}

bool string_to_uint32(const std::string& str, uint32_t& val)
{
	if (sscanf(str.c_str(), "%" SCNu32, &val) != 1) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("string_to_uint32 conversion failed for %", str));
		return false;
	}
	return true;
}

bool string_to_int64(const std::string& str, int64_t& val)
{
	if (sscanf(str.c_str(), "%" SCNi64, &val) != 1) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("string_to_int64 conversion failed for %", str));
		return false;
	}
	return true;
}

bool string_to_uint64(const std::string& str, uint64_t& val)
{
	if (sscanf(str.c_str(), "%" SCNu64, &val) != 1) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("string_to_uint64 conversion failed for %", str));
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

	// It is possible that the conversion was successful and another thread
	// has set errno meanwhile but as most conversions are currently not
	// checked for error conditions this is better than nothing.
	if (errno == ERANGE) {
		MOJO_DEBUG_MSG(
		    STRING_CONVERT,
		    compose("string_to_double possible conversion failure for %", str));
		// There should not be any conversion failures as we control the string
		// contents so returning false here should not have any impact...
		return false;
	}
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

bool int16_to_string(int16_t val, std::string& str)
{
	char buffer[CONVERT_BUF_SIZE];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIi16, val);

	if (retval <= 0 || retval >= (int)sizeof(buffer)) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("int16_to_string conversion failure for %", str));
		return false;
	}
	str = buffer;
	return true;
}

bool uint16_to_string(uint16_t val, std::string& str)
{
	char buffer[CONVERT_BUF_SIZE];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIu16, val);

	if (retval <= 0 || retval >= (int)sizeof(buffer)) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("uint16_to_string conversion failure for %", str));
		return false;
	}
	str = buffer;
	return true;
}

bool int32_to_string(int32_t val, std::string& str)
{
	char buffer[CONVERT_BUF_SIZE];

	int retval = g_snprintf(buffer, sizeof(buffer), "%" PRIi32, val);

	if (retval <= 0 || retval >= sizeof(buffer)) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("int32_to_string conversion failure for %", str));
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
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("uint32_to_string conversion failure for %", str));
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
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("int64_to_string conversion failure for %", str));
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
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("uint64_to_string conversion failure for %", str));
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

	char* d_cstr = g_ascii_dtostr(buffer, sizeof(buffer), val);

	if (d_cstr == NULL) {
		MOJO_DEBUG_MSG(STRING_CONVERT,
		               compose("double_to_string conversion failure for %", val));
		return false;
	}
	str = d_cstr;
	return true;
}

} // namespace mojo
