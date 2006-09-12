#ifndef GLEAM_THREAD_MAP_INCLUDED
#define GLEAM_THREAD_MAP_INCLUDED

#include <string>
#include <map>

#include <glibmm/thread.h>

namespace gleam {

using std::string;
using std::map;

class ThreadMap
{
public:

	/**
	  This must be called from within a new thread and it can
	  only be called once.
	  */
	void register_thread (const string& thread_name);

	/**
	  This must be called before termination of a thread from
	  within the thread being terminated to unregister the
	  thread. The thread name isn't really needed but it is 
	  required for slightly increased anally retentive safety.
	  */
	void unregister_thread (const string& thread_name);
	
	/**
	  This can be called to ensure the currently running thread
	  is the thread specified by the thread_name parameter.
	  \param thread_name The expected name of the thread making
	  the call.
	  \return True if thread_name is the thread making the call.

	  \code

	  // assert that the current thread is the "Process Thread"
	  g_assert(GLEAM::thread_map().is_thread("Process Thread"));

	  \endcode

	  */
	bool is_thread (const string& thread_name);
	
	/**
	   This is for convenience and readability
	 */
	bool is_not_thread (const string& thread_name);
	
	/**
	  \return The name registered for the current thread. If
	  The thread is not registered with the thread map then the
	  string "Unregistered Thread" will be returned.
	  */
	const string current_thread_name ();

private:
	
	typedef map<string, Glib::Thread*> ThreadMapType;

	ThreadMapType		m_thread_map;
	Glib::Mutex		m_map_mutex;

	void print_thread_map () const;
};

} // namespace gleam

#endif // GLEAM_THREAD_MAP_INCLUDED

