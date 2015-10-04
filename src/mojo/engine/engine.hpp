#ifndef MOJO_ENGINE_H
#define MOJO_ENGINE_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/engine/node.hpp"
#include "mojo/engine/graph.hpp"
#include "mojo/engine/clock_source.hpp"
#endif

namespace mojo {

/**
 * Does the Engine have to be aware of the transport state?
 *
 * Port offsets are in units of time(us or ns?) and are unrelated to transport
 * state in that they still exist in a system without a transport system as the
 * engine cycle continues regardless of transport state which suggests
 * transport is external to engine and independent.
 *
 * When the transport state changes from stopped transport state
 * transitions need to be handled somewhere
 *
 * Although the Engine processing cycle is driven by the ClockSource the
 * internal processing in the engine may be divided up as  necessary. What
 * units should the engine divisions be based on? time or samples. If time how
 * do we handle rounding etc. I guess rounding happens either way, although it
 * is unlikely that sub-sample accuracy is required.
 *
 * so for instance port connections/disconnections can be handled and in an
 * atomic/per cycle fashion which suggests that the engine is somewhat
 * responsible.
 *
 * Engine receives events from the Application and processes them, for instance
 * transport change events. It also sends events to the application, for
 * instance buffer fill and buffer write events
 *
 * The state of the Engine reflects the state of the project but the engine does
 * not have access and does not depend on the Project or Application classes.
 * This allows the Engine API to be reusable.
 *
 * The processing is performed by the Engine using the optimal number of
 * threads for the system or a specific number if set.
 *
 * The process cycle starts based on a callback from the clock source which
 * may be a callback from the audio device
 *
 * The Application registers an event handler callback to receive all the events
 * issued by the engine and then processes them.
 *
 * The Engine process cycle is broken up into chunks of data/time which can be
 * different from the chunk size of the AudioDevice callback.
 *
 * The engine contains a number of nodes that are connected to form a graph that
 * determines data flow.
 *
 * Each Node can have zero or more input and output ports. A Node doesn't have
 * to have same number of input ports. For instance a Node could take a stereo
 * input using two inputs and have 6 output ports for 5.1 surround sound.
 *
 * Or a node could have have a input port that receives a stereo audio signal
 * in a single port. This means ports will have to have a data type property,
 * possibly defined by a URI etc.
 *
 * A Node might also have different types of ports, for instance a midi input
 * port and an audio output port in the case of an Midi Instrument track
 *
 * The Engine isn't responsible for saving and restoring connection state, but
 * emits a graph changed events to another class to do that.
 *
 * - Removing Nodes doesn't cause clicks.
 * - Export/Render paths are the same as normal processing
 * - Testing of the engine can be performed
 *
 * When a graph has to be rendered to use in a bounce/freeze does that have to
 * be done while disconnected from audio driver/clock source? I think it would
 * simplify things greatly if it did.
 */
class Engine {
public: // ctors
	Engine();

	~Engine();

public: // Interface

	/**
	 * sync?
	 *
	 * Start the Engine, A clock source must first be set.
	 */
	bool start();

	// void is_running ();

	/**
	 * sync?
	 *
	 * Stop the Engine.
	 */
	bool stop();

	/**
	 * Get a copy of the current graph, so that nodes can be added/removed,
	 * connected/disconnected etc.
	 */
	Graph* get_graph ();

	/**
	 * Set the graph to be used in the next iteration of the engine processing
	 * cycle. I guess a graph changed signal/will need to be emitted? or is
	 * that performed by a higher level class.
	 */
	void set_graph (Graph*);

	/**
	 * This must stop the Engine and restart or stop must be called first?
	 */
	bool set_clock_source(ClockSource* clock);

	ClockSource* get_clock_source() const;

private:

	// TODO Make NonCopyable
};

} // namespace mojo

#endif // MOJO_ENGINE_H
