#ifndef MOJO_CORE_DEBUG_REGISTRY_H
#define MOJO_CORE_DEBUG_REGISTRY_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

class DebugRegistry
{
private: // types

	using DomainMapType = std::map<std::string, uint32_t>;

public: // ctors

	DebugRegistry () : m_domain_index(0) { };

public: // methods

	uint32_t get_domain_index (const char* domain)
	{
		// try and find domain in map
		DomainMapType::const_iterator i = m_domain_map.find(domain);
		if (i != m_domain_map.end())
		{
			return i->second;
		}
		// insert new domain
		m_domain_map.insert(std::make_pair(domain, m_domain_index));
		m_enabled_index.push_back (false);
		// assert(map.size() == cache.size());
		return m_domain_index++;
	}

	void get_domains (std::vector<std::string>& domains)
	{
		for (auto& i : m_domain_map)
		{
			domains.push_back(i.first);
		}
	}

	bool get_enabled (uint32_t domain_index)
	{
		// assert(domain_index <= m_enabled_index.size());

		return m_enabled_index[domain_index];
	}

	void set_enabled (uint32_t domain_index, bool enable)
	{
		m_enabled_index[domain_index] = enable;
	}

private:

	uint32_t m_domain_index;

	DomainMapType m_domain_map;

	std::vector<bool> m_enabled_index;

};

} // namespace mojo

#endif // MOJO_CORE_DEBUG_REGISTRY_H
