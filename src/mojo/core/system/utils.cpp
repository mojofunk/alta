#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/system/utils.hpp"
#endif

namespace mojo {

std::string getenv(const std::string& name)
{
	const char* const env = g_getenv(name.c_str());
	if (env)
		return env;
	else
		return std::string();
}

} // namespace mojo
