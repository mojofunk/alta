#include "debug.hpp"

#include <iostream>
#include <map>
#include <vector>

#include "mojo/string/compose.hpp"

using DomainMapType = std::map<std::string, uint32_t>;

namespace {

DomainMapType&
get_domain_map()
{
	static DomainMapType domain_map;
	return domain_map;
}

uint32_t&
get_domain_index()
{
	static uint32_t domain_index = 0;
	return domain_index;
}

std::vector<bool>&
get_enabled_index()
{
	static std::vector<bool> enabled_index;
	return enabled_index;
}

} // anonymous namespace

namespace mojo {

namespace debug {

uint32_t
get_domain_index (const char* domain)
{
	static uint32_t domain_index = 0;

	// try and find domain in map
	DomainMapType::const_iterator i = get_domain_map().find(domain);
	if (i != get_domain_map().end())
	{
		return i->second;
	}
	// insert new domain
	get_domain_map().insert(std::make_pair(domain, domain_index));
	get_enabled_index().push_back (false);
	// assert(map.size() == cache.size());
	return domain_index++;
}

void
get_domains (std::vector<std::string>& domains)
{
	for (auto& i : get_domain_map())
	{
		domains.push_back(i.first);
	}
}

bool
get_enabled (uint32_t domain_index)
{
	// assert(domain_index <= get_enabled_index.size());

	return get_enabled_index()[domain_index];
}

void
set_enabled (uint32_t domain_index, bool enabled)
{
	get_enabled_index()[domain_index] = enabled;
}

void
log (const char* file, int line, uint32_t domain, const std::string& str)
{
	std::cerr << compose("% : % : % : %", file, line, domain, str) << std::endl;
}

} // namespace debug

} // namespace mojo
