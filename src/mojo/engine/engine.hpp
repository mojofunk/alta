
#ifndef MOJO_ENGINE
#define MOJO_ENGINE

namespace mojo {

/**
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
 *  - processes incoming events including buffer filled events, stream modifications
 *    and transport changes.
 *
 *  - reads data from the audio device and performs any necessary processing
 *    including posting a buffer write request if the stream is record enabled 
 *
 *  - write data to the audio device
 *
 *  None of the Engine buffers are exposed outside of the Engine class. During
 *  the process cycle the engine checks the state of the buffers and if any need
 *  to be filled then a buffer fill request is sent via the Engine event queue.
 *
 *  The Session thread periodically calls Engine::get_events to get all the
 *  events issued by the engine and then processes them.
 */
class Engine
{

};

} // namespace mojo

#endif
