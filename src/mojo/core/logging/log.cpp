#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source.hpp"
#include "mojo/core/logging/log.hpp"
#endif

namespace mojo {

void
log (const char* log_domain, const std::string& msg)
{
	std::cerr << msg << std::endl;
}

}
