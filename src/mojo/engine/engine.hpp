#ifndef MOJO_ENGINE_H
#define MOJO_ENGINE_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/engine/node.hpp"
#include "mojo/engine/clock_source.hpp"
#endif

namespace mojo {

/**
 * Engine recieves events from the Application and processes them, for instance
 * transport change events. It also sends events to the application, for
 * instance buffer fill and buffer write events
 *
 * The state of the Engine reflects the state of the project but the engine does
 * not have access and does not depend on the Project or Application classes.
 * This allows the Engine API to be reusable.
 *
 * The Engine has a clock signal that it receives from the audio device
 *
 * The processing is performed by the Engine using the optimal number of
 * threads for the system or a specific number if set.
 *
 * The Engine
 *
 *  - waits for periodic wakeup/callback from the audio device
 *
 *  - processes incoming events including buffer filled events, stream
 *    modifications and transport changes.
 *
 *  - reads data from the audio device and performs processing(possibly
 *    concurrently) including posting a buffer write request if the stream
 *    is record enabled
 *
 *  - writes data to the audio device
 *
 * The Application registers an event handler callback to recieve all the events
 * issued by the engine and then processes them.
 *
 * The Engine needs to return a reference to a structure that represents an
 * internal representation of a track
 *
 * should external classes have direct access to Node controls or should all
 * parameter changes go through the engine so it can mediate them?
 *
 * The Engine process cycle is broken up into chunks of data/time which could be
 * different from the chunk size of the AudioDevice callback.
 *
 * The engine contains a number of nodes that are connected to form a graph that
 * determines data flow.
 *
 * Each Node can have zero or more input and output ports. A Node doesn't have
 * to have same number of input ports. For instance a Node could take a stereo
 * input using two inputs and have 6 output ports for 5.1 surround sound.
 *
 * Or a node could have have a input port that recieves a stereo audio signal
 * in a single port. This means ports will have to have a data type property,
 * possibly defined by a URI etc.
 *
 * A Node might also have different types of ports. for instance a midi input
 * port and an audio output port in the case of an Midi Instrument track
 *
 * To make the Engine versatile and ignorant of Node implementations I think
 * Nodes must be added and removed from the Engine. This would mean Node is just
 * an interface that a class would implement.
 *
 * The Engine would still have to manage connections between the Nodes and be
 * responsible for syncronizing thread access to buffers during the process
 * cycle
 *
 * The Engine isn't responsible for saving and restoring connection state, but
 * sends events to another class to do that.
 *
 * The engine may have to expose a sort of transaction interface where a series
 * of additions and connections can be queued but not actually processed in the
 * engine thread context until end_transaction() is called.
 *
 */
class Engine {
public: // ctors
	Engine();

	~Engine();

public: // Interface

	/**
	 * Start the Engine, A clock source must first be set.
	 */
	bool start();

	// void is_running ();

	bool stop();

	/**
	 * I think this should be sync call which means the calling thread will
	 * have to wait until the node is added to the graph.
	 *
	 * @return true if the node is successfully added, the node won't be
	 * inserted and or connected until the next clock event/iteration
	 */
	bool add_node(Node* node);

	/**
	 * I think this should be sync call which means the calling thread will
	 * have to wait until the node is removed from the graph.
	 *
	 * @return true if the node is successfully removed, the node won't be
	 * removed or disconnected until the next clock event/iteration
	 */
	void remove_node(Node* node);

	/**
	 * This must stop the Engine and restart?
	 */
	void set_clock_source(ClockSource* clock);

	ClockSource* get_clock_source() const;

private:

	// TODO Make NonCopyable
};

} // namespace mojo

#endif // MOJO_ENGINE_H
