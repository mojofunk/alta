#ifndef MOJO_ENGINE_H
#define MOJO_ENGINE_H

#include "mojo/audio_driver/forward.hpp"

namespace mojo {

class Node;

/**
 * Engine recieves events from the Application and processes them, for instance
 * transport change events. It also sends events to the application, for
 *instance
 * buffer fill and buffer write events
 *
 * The state of the Engine reflects the state of the project but the engine does
 * not have access and does not depend on the Project or Application classes.
 *This
 * allows the Engine API to be reusable.
 *
 * The Engine has a clock signal that it receives from the audio device
 *
 * The processing is performed by the Engine using the optimal number of threads
 *for
 * the system or a specific number if set.
 *
 * The Engine
 *
 *  - waits for periodic wakeup/callback from the audio device
 *
 *  - processes incoming events including buffer filled events, stream
 *modifications
 *    and transport changes.
 *
 *  - reads data from the audio device and performs processing(possibly
 *concurrently)
 *    including posting a buffer write request if the stream is record enabled
 *
 *  - writes data to the audio device
 *
 * The Application registers an event handler callback to recieve all the events
 *issued
 * by the engine and then processes them.
 *
 * The AudioDevice interface hides the implementation of the audio driver
 *
 * The Engine needs to return a reference to a structure that represents an
 * internal representation of a track
 *
 * should external classes have direct access to Node controls or should all
 *parameter
 * changes go through the engine so it can mediate them?
 *
 * The Engine process cycle is broken up into chunks of data/time which could be
 * different from the chunk size of the AudioDevice callback.
 *
 * The engine contains a number of nodes that are connected to form a graph that
 * determines data flow.
 *
 * Each Node can have zero or more input and output ports. A Node doesn't have
 *to
 * have same number of input ports. For instance a Node could take a stereo
 *input
 * using two inputs and have 6 output ports for 5.1 surround sound.
 *
 * A Node might also have different types of ports. for instance a midi input
 *port
 * and an audio output port in the case of an Midi Instrument track
 *
 * To make the Engine versatile and ignorant of Node implementations I think
 *Nodes
 * must be added and removed from the Engine. This would mean Node is just an
 * interface that a class would implement.
 *
 * The Engine would still have to manage connections between the Nodes and be
 * responsible for syncronizing thread access to buffers during the process
 *cycle
 *
 * The Engine isn't responsible for saving and restoring connection state, but
 * sends events to another class to do that.
 *
 *
 */
class Engine {
public: // ctors
	Engine();

	~Engine();

public: // Interface
	void start();

	// void is_running ();

	void stop();

	void add_node(Node* node);

	void remove_node(Node* node);

	/**
	 * This must stop the Engine, change devices
	 * and restart?
	 */
	void set_audio_device(AudioDevice* dev);

	AudioDevice* get_audio_device() const;
};

} // namespace mojo

#endif // MOJO_ENGINE_H
