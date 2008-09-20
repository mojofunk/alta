
#ifndef MOJO_SESSION
#define MOJO_SESSION

#include <mojo/typedefs.hpp>

namespace mojo {

/**
 * A session processes a project to make noise :)
 *
 * A session manages a task thread that asyncronously runs all tasks that
 * have been queued.
 *
 * Tasks:
 *
 * Read data from disk and fill the playback buffers
 * Write data from record buffers to disk
 * Modify project
 *
 * The task thread also dispatches events to the session bus. The session bus
 * is how the clients recieve all asyncronous messages.
 *
 * port/stream connection graph/state....hmmmm isn't that part of the project
 *
 * bus configuration?
 *
 * is the session state stored in a separate file to the project?, what
 * happens if the project is opened without the session data? no connections?
 *
 * The state of the project must remain constant while it is being processed 
 * by the session because any changes could lead to inconsistancies..how?.
 * At least no allocation or deallocation can occur in the processing thread/s
 * this means that if for instance a track is removed it must be deferred and
 * performed in another thread.
 *
 * If the state of the entire project must be constant while processing
 * the data graph and modifying the project must not interrupt processing,
 * which could happen if any locking is used.
 *
 * What might be much easier is if the processing occured in a non-RT
 * thread or threads and the RT thread just copies data between buffers
 * but that would mean introducing some control latency.
 * 
 * What about an approach where if an object is modified a new state based
 * on the current state is created and then put into a queue for the
 * RT thread to atomically update when it is safe to do so. A mechanism would
 * then be needed to notify about changes which could be done by sending the
 * updates back via a ringbuffer to be processed.
 *
 * As state changes are made via an object, the atomic update could contain a
 * functor or virtual method that is executed by a non-RT thread once the  
 *
 * I think it is important to keep locking and syncronization as simple and
 * as centralized as possible.
 *
 * The RT thread:
 *
 *  - reads data from ringbuffer/s that contain input data from the audio device
 *    into a place appropriate for processing.
 *
 *  - signals processing threads to process the data, the processing threads
 *    then wake up and process the entire graph.
 *
 *  - waits for every non-RT processing thread pool to complete processing, 
 *    possibly using a semaphore.
 *  
 *  - writes data into the ringbuffer/s that contain output data for the audio
 *    device.
 *
 *  - processes state change events.
 *
 * A project is considered to be in an "Offline" state
 * when it is not part of a session.
 *
 * A project must be able to be edited "Offline"
 *
 * When a project is "Offline" it can be edited directly
 * in the current thread.
 *
 * When a Project is part of a Session then all modifications
 * to the project must be performed in a single thread.
 *
 * A Project can be modified while the transport is 
 * in a rolling state.
 *
 * Saving a Project requires that the Project is read-only
 * while it is being saved.
 *
 */
class Session
{
public:

	Session();

public:

	/**
	 * When setting the project for the session
	 * if the native samplerate of the project
	 * and the rate of the AudioDevice are different
	 * then the audio device is re-opened to match
	 * the native rate.
	 */
	void set_project (ProjectSP proj);

	ProjectSP get_project () const;

	void set_audio_device (AudioDevice* dev);

	AudioDevice* get_audio_device () const;

	// Access to auditioning functions
	
private:

	// transport_ptr
	
	// project_ptr
};

} // namespace mojo

#endif
