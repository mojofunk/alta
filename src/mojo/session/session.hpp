
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
 *
 * A new project must be able to be created without needing to specify
 * a project/recording directory. This implies that when enabling record
 * that it should return an error status that allows the client to set a
 * record directory and try again.
 *
 * Several projects must be able to be open at once but only one project
 * can be active at once.
 *
 * Only an active project can be modified?
 *
 * methods like save_project and close_project don't take a project
 * identifier argument. Does that mean they apply to the current active
 * project?
 *
 * I think it would simplify things greatly if all objects are managed
 * by the Session or at least creation and destruction of objects is controlled
 * through the Session.
 *
 * This means that clients can treat any objects that are created through the
 * session as managed but do not participate in that management.
 *
 */
class Session
{
public: // ctors

	Session ();

	~Session ();

public: // public API

	/**
	 * Create a new project.
	 * Async
	 */
	void new_project ();

	/**
	 * If the native samplerate of the project
	 * and the rate of the AudioDevice are different
	 * then the audio device is re-opened to match
	 * the native rate.
	 *
	 * Async
	 */
	void open_project (const std::string& project_file);

	/**
	 * Async
	 */
	void save_project_as (const std::string& filename);

	/**
	 * Will send an error to the session bus if the if
	 * project file name hasn't been set
	 *
	 * Async
	 */
	void save_project ();

	/**
	 * should return status
	 * Async
	 */
	void close_project ();

	// Access to auditioning functions
	
private:

	// transport_ptr
	
	// project_ptr
};

} // namespace mojo

#endif
