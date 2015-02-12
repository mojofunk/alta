#ifndef MOJO_CORE_DEBUG_H
#define MOJO_CORE_DEBUG_H

#include <iostream>
#include <string>
#include <vector>


#include <glib.h>

namespace mojo {

namespace debug
{
	uint32_t get_domain_index (const char* domain);
	void get_domains (std::vector<std::string>& domains);

	void set_enabled (uint32_t domain_index, bool enable);
	bool get_enabled (uint32_t domain_index);

	void log (const char* file, int line, uint32_t domain, const std::string& str);
}

} // namespace mojo

#define MOJO_DEBUG_DOMAIN(domain_name) namespace { uint32_t domain_name = mojo::debug::get_domain_index( # domain_name ); }

#define MOJO_DEBUG_MSG(domain, str) if (mojo::debug::get_enabled(domain)) { mojo::debug::log (__FILE__, __LINE__, domain, str); }

#define MOJO_DEBUG(domain) if (mojo::debug::get_enabled(domain)) { mojo::debug::log (__FILE__, __LINE__, domain, ""); }

#endif
