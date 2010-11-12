
#ifndef MOJO_ENGINE
#define MOJO_ENGINE

#include <mojo/core/typedefs.hpp>

namespace mojo {

/**
 * Engine recieves events from the Session and processes them, for instance
 * transport change events. It also sends events to the session, for instance
 * buffer fill and buffer write events.
 *
 * The state of the Engine reflects the state of the project but the engine does
 * not have access and does not depend on the Project or Session classes. This
 * allows the Engine API to be reusable.
 *
 * The processing is performed by the Engine using the optimal number of threads for
 * the system or a specific number if set.
 *
 * The Engine
 *
 *  - waits for periodic wakeup/callback from the audio device
 *
 *  - processes incoming events including buffer filled events, stream modifications
 *    and transport changes.
 *
 *  - reads data from the audio device and performs processing(possibly concurrently)
 *    including posting a buffer write request if the stream is record enabled 
 *
 *  - writes data to the audio device
 *
 * None of the Engine buffers are exposed outside of the Engine class. During
 * the process cycle the engine checks the state of the buffers and if any need
 * to be filled then a buffer fill request is sent via the Engine event queue.
 *
 * The Session thread periodically calls Engine::get_events to get all the
 * events issued by the engine and then processes them. The Engine could signal the
 * Session to run somehow perhaps.
 *
 * When the Engine issues a buffer fill event, the engine provides the array/buffer
 * to be written into.
 *
 * The AudioDevice interface hides the implementation of the audio driver
 *
 * The Engine needs to return a reference to a structure that represents an
 * internal representation of a track
 *
 */
class Engine
{
public: // ctors

	Engine ();

	~Engine ();

public: // Interface

	void start ();

	//void is_running ();

	void stop ();

	/**
	 * This must stop the Engine, change devices
	 * and restart?
	 */
	void set_audio_device (AudioDevice* dev);

	AudioDevice* get_audio_device () const;
};

} // namespace mojo

#endif
