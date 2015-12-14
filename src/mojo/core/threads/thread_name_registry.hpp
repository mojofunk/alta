#ifndef MOJO_THREAD_NAME_REGISTRY_H
#define MOJO_THREAD_NAME_REGISTRY_H

/**
 * Ideally this would be lock-free or at least use a ReadWriteLock/RCU or
 * perhaps TLS, but this will do for now.
 */
template <class StringType>
class ThreadNameRegistry {
public:
	typedef StringType string_type;

public:
	bool register_thread(const StringType& thread_name)
	{
		std::unique_lock<std::mutex> lock(m_thread_name_map_mutex);

		return m_thread_name_map.insert(std::make_pair(std::this_thread::get_id(),
		                                               thread_name)).second;
	}

	bool unregister_thread()
	{
		std::unique_lock<std::mutex> lock(m_thread_name_map_mutex);
		return (m_thread_name_map.erase(std::this_thread::get_id()));
	}

	/**
	 * If the thread is not known should the id be converted to a string rather
	 * than returning a fixed string as at least that will allow differentiating
	 * between threads.
	 */
	StringType get_thread_name()
	{
		std::unique_lock<std::mutex> lock(m_thread_name_map_mutex);
		typename ThreadNameRegistryType::const_iterator i =
		    m_thread_name_map.find(std::this_thread::get_id());

		if (i != m_thread_name_map.end()) {
			return i->second;
		}
		return unknown_thread_name();
	}

	static const char* const unknown_thread_name() { return "Unknown Thread"; }

private:
	typedef typename std::map<std::thread::id, const string_type>
	    ThreadNameRegistryType;
	ThreadNameRegistryType m_thread_name_map;
	std::mutex m_thread_name_map_mutex;
};

#endif // MOJO_THREAD_NAME_REGISTRY_H
