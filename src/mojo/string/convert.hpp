
#ifndef MOJO_STRING_CONVERT
#define MOJO_STRING_CONVERT

#include <cstdint>
#include <string>

#include "mojo/core/visibility.hpp"

/**
 * Locale independent string conversion utility functions.
 */
namespace mojo {

MOJO_API bool string_to_bool (const std::string& str, bool& val);

MOJO_API bool string_to_int16 (const std::string& str, int16_t& val);

MOJO_API bool string_to_int32 (const std::string& str, int32_t& val);

MOJO_API bool string_to_int64 (const std::string& str, int64_t& val);

MOJO_API bool string_to_float (const std::string& str, float& val);

MOJO_API bool string_to_double (const std::string& str, double& val);


MOJO_API bool bool_to_string (bool val, std::string& str);

MOJO_API bool int16_to_string (int16_t val, std::string& str);

MOJO_API bool int32_to_string (int32_t val, std::string& str);

MOJO_API bool int64_to_string (int64_t val, std::string& str);

MOJO_API bool float_to_string (float val, std::string& str);

MOJO_API bool double_to_string (double val, std::string& str);

} // namespace mojo

#endif // MOJO_STRING_CONVERT

