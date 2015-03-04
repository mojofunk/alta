#include <iostream>
#include <map>
#include <vector>

#ifndef MOJO_CORE_AMALGAMATED

#include "mojo/core/debug/debug.hpp"

#include "mojo/core/string/compose.hpp"

#endif // MOJO_CORE_AMALGAMATED

namespace mojo {

namespace debug {

DebugRegistry&
get_registry()
{
	static DebugRegistry debug_registry;
	return debug_registry;
}

uint32_t
get_domain_index (const char* domain_name)
{ return get_registry().get_domain_index(domain_name); }

bool
get_enabled (uint32_t domain_index)
{ return get_registry().get_enabled(domain_index); }

void
set_enabled (uint32_t domain_index, bool enable)
{ return get_registry().set_enabled(domain_index, enable); }

void
log_message (const char* file, int line, uint32_t domain, const std::string& str)
{
	std::cerr << compose("% : % : % : %", file, line, domain, str) << std::endl;
}

} // namespace debug

} // namespace mojo
