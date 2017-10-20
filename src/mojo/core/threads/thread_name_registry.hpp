#ifndef MOJO_THREAD_NAME_REGISTRY_H
#define MOJO_THREAD_NAME_REGISTRY_H

/**
 * Ideally this would be lock-free or perhaps use TLS, but using a try_lock for
 * reading the thread name should be sufficient for now.
 */
template <class StringType>
class ThreadNameRegistry
{
public:
	typedef StringType string_type;

public:
	bool register_thread(const char* const thread_name)
	{
		std::lock_guard<std::mutex> lock(m_thread_name_map_mutex);

		bool inserted =
		    m_thread_name_map
		        .insert(std::make_pair(std::this_thread::get_id(), thread_name))
		        .second;

		return inserted;
	}

	bool unregister_thread()
	{
		std::lock_guard<std::mutex> lock(m_thread_name_map_mutex);
		return (m_thread_name_map.erase(std::this_thread::get_id()));
	}

	/**
	 * @return Return the thread name associated with the thread_id or a string
	 * representing an unknown thread name.
	 */
	StringType get_thread_name(std::thread::id const& thread_id)
	{
		std::unique_lock<std::mutex> lock(m_thread_name_map_mutex, std::try_to_lock);

		if (lock.owns_lock()) {
			StringType thread_name;
			typename ThreadNameRegistryType::const_iterator i =
			    m_thread_name_map.find(thread_id);

			if (i != m_thread_name_map.end()) {
				thread_name = i->second;
				return thread_name;
			}
		} else {
			// debug message
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
