
#include <glib.h>

#include <libgleam/utils.hpp>

namespace gleam {

std::string
getenv(const std::string& name)
{
	const char* const env = g_getenv (name.c_str());
	if (env) return env;
	else return std::string();
}

} // namespace gleam
