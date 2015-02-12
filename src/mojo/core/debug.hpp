#ifndef MOJO_CORE_DEBUG_H
#define MOJO_CORE_DEBUG_H

#include <string>
#include <vector>

#include "mojo/core/debug_registry.hpp"

namespace mojo {

namespace debug {

	DebugRegistry& get_registry ();

	uint32_t get_domain_index (const char* domain_name);

	bool get_enabled (uint32_t domain_index);

	void set_enabled (uint32_t domain_index, bool enable);

	void log_message (const char* file, int line, uint32_t domain, const std::string& str);

} // namespace debug

} // namespace mojo

#define MOJO_DEBUG_DOMAIN(domain_name) namespace { uint32_t domain_name = mojo::debug::get_domain_index( # domain_name ); }

#define MOJO_DEBUG_MSG(domain, str) if (mojo::debug::get_enabled(domain)) { mojo::debug::log_message(__FILE__, __LINE__, domain, str); }

#define MOJO_DEBUG(domain) if (mojo::debug::get_enabled(domain)) { mojo::debug::log_message (__FILE__, __LINE__, domain, ""); }

#endif
