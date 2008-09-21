
#ifndef MOJO_SESSION
#define MOJO_SESSION

#include <string>

namespace mojo {

/**
 * The session class is the public API of libmojo. All interaction with a
 * project must be done through the session. This is to ensure that the state
 * of the project is modified by a single thread. None of the project classes
 * are exposed by session.
 *
 * The session state is stored in a separate file to the project and contains
 * nothing project specific.
 *
 * I think it is important to keep locking and syncronization as simple and
 * as centralized as possible.
 *
 * A session manages a task thread that asyncronously runs all tasks that
 * have been queued. some of these tasks are:
 *
 * Read data from disk and fill the playback buffers
 * Write data from record buffers to disk
 * Modifications to the project
 *
 * The Session thread also dispatches events to the session event bus. The
 * session event bus is how the clients recieve all asyncronous messages.
 */
class Session
{
public: // ctors

	Session ();

	~Session ();

public: // public API

	/**
	 * Create a new project.
	 */
	void new_project (const std::string& project_folder);

	/**
	 * If the native samplerate of the project
	 * and the rate of the AudioDevice are different
	 * then the audio device is re-opened to match
	 * the native rate.
	 */
	void open_project (const std::string& project_file);

	void save_project_as (const std::string& filename);

	/// should return error status if project file name
	/// hasn't been set
	void save_project ();

	/// should return status
	void close_project ();

	// Access to auditioning functions
	
private:

	// transport_ptr
	
	// project_ptr
};

} // namespace mojo

#endif
