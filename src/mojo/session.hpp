
#ifndef MOJO_SESSION_INCLUDED
#define MOJO_SESSION_INCLUDED

namespace mojo {

/**
 * A session processes a project to make noise :)
 *
 * It contains a thread to read data from disk
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
 * but that would mean introducing some latency.
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
 */
class Session
{
public:

	// the session takes ownership of the session
	Session(Project* p);

private:

	// transport_ptr
	
	// project_ptr
}

} // namespace mojo

#endif
