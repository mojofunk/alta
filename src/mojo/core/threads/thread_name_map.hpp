#ifndef MOJO_THREAD_NAME_MAP_H
#define MOJO_THREAD_NAME_MAP_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

template <class StringType>
class ThreadNameMap {
public:
	typedef StringType string_type;

public:
	bool insert_name(const StringType& thread_name)
	{
		std::unique_lock<std::mutex> lock(m_thread_name_map_mutex);

		return m_thread_name_map.insert(std::make_pair(std::this_thread::get_id(),
		                                               thread_name)).second;
	}

	bool erase_name(const StringType& thread_name)
	{
		std::unique_lock<std::mutex> lock(m_thread_name_map_mutex);
		return (m_thread_name_map.erase(std::this_thread::get_id()));
	}

	StringType get_name()
	{
		std::unique_lock<std::mutex> lock(m_thread_name_map_mutex);
		typename ThreadNameMapType::const_iterator i =
		    m_thread_name_map.find(std::this_thread::get_id());

		if (i != m_thread_name_map.end()) {
			return i->second;
		}
		return unknown_thread_name();
	}

	static const char* const unknown_thread_name() { return "Unknown Thread"; }

private:
	typedef typename std::map<std::thread::id, const string_type>
	    ThreadNameMapType;
	ThreadNameMapType m_thread_name_map;
	std::mutex m_thread_name_map_mutex;
};

} // namespace mojo

#endif // MOJO_THREAD_NAME_MAP_H