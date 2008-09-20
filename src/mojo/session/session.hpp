
#ifndef MOJO_SESSION
#define MOJO_SESSION

#include <mojo/typedefs.hpp>

namespace mojo {

/**
 * The session class is the public API of libmojo. All interaction with a
 * project must be done through the session.
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
 * The task thread also dispatches events to the session bus. The session bus
 * is how the clients recieve all asyncronous messages.
 *
 * The processing thread is managed by the Engine class. The processing
 * thread recieves events from the Session and processes them, for instance
 * transport change events. It also sends events to the session, for instance
 * buffer fill and buffer write events.
 *
 * The state of the Engine reflects the state of the project but the engine does
 * not have access and does not depend on the Project or Session classes. This
 * allows the Engine API to be reusable.
 *
 * The Engine
 *
 *  - process incoming events including buffer fill events, stream modifications
 *    and transport changes.
 *
 *  - reads data from the audio device and performs any necessary processing
 *    including posting a buffer write request if the stream is record enabled 
 *
 *  - write data to the audio device
 *
 */
class Session
{
public:

	Session();

public:


	/**
	 * Create a new project.
	 */
	void new_project (const path& project_folder);

	/**
	 * If the native samplerate of the project
	 * and the rate of the AudioDevice are different
	 * then the audio device is re-opened to match
	 * the native rate.
	 */
	void open_project (const path& project_file);

	void save_project_as (const string& filename);

	/// should return error status if project file name
	/// hasn't been set
	void save_project ();

	/// should return status
	void close_project ();

	void set_audio_device (AudioDevice* dev);

	AudioDevice* get_audio_device () const;

	// Access to auditioning functions
	
private:

	// transport_ptr
	
	// project_ptr
};

} // namespace mojo

#endif
