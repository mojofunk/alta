#ifndef MOJO_ENGINE_H
#define MOJO_ENGINE_H

namespace mojo {

/**
 * Time taken to process the Engine graph is determined by external means. The
 * Engine is only concerned with ensuring the nodes are processed in the
 * correct order and only once per cycle independent of how many threads are
 * used to process the graph.
 *
 * Connections between nodes are handled by an external class. The Engine treats
 * connections between nodes as static while processing the graph. If some
 * action needs to be performed(perhaps over more than one cycle) externally
 * before updating the graph with the nodes disconnected/removed/etc
 *
 * Ports and Buffer data offsets are not relevant to the engine
 *
 * Transport state changes are not relevant to the engine.
 *
 * The processing is performed by the Engine using a variable number of threads
 * It is up to an external class to determine the appropriate number of threads
 * to use for processing. The Engine has a pool of threads used to process the
 * graph. What class is responsible for creating those threads? Does Engine
 * need access to an external class to create new threads for flexibility.
 *
 * The engine is not concerned by how long it takes to process the
 * graph(although we will want to measure it). The amount of processing
 * performed by a class when a node processing callback is entirely up to the
 * external factors.
 *
 * Do we want a more flexible method of processing than threads like
 * workers/contexts to be able to reduce the total amount of threads...probably
 * not.
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
 * The Engine isn't responsible for saving and restoring connection state, the
 * state of the connections and nodes in the engine are a reflection of
 * external state so it is the responsibility of another class to monitor
 * changes in that external state and update the Engine's graph to reflect
 * that.
 *
 * Removing a Node should not cause clicks, I think this will be the
 * responsibility of another class to do this. For instance when a Track is
 * removed from the graph and it is playing back audio data then it will need
 * to be set to a state where it is fading out for a period of time before it
 * can be removed from the graph.
 *
 * Export/Render paths should use the same processing paths as normal
 * processing and be performed in realtime(to capture external sources) and
 * faster than realtime.
 *
 * It is important that testing of the engine can be performed easily and that
 * the engine is a reusable component that can be used in many applications.
 *
 * When a graph has to be rendered to use in a bounce/freeze does that have to
 * be done while disconnected from audio driver/clock source? I think it would
 * simplify things greatly if it did.
 *
 * This class perhaps should be called GraphProcessor
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
	 * connected/disconnected etc. As a copy is returned changing the graph
	 * won't change the graph in the engine until a new graph is set with
	 * set_graph.
	 */
	Graph* get_graph();

	/**
	 * Set the graph to be used in the next iteration of the engine processing
	 * cycle. I guess a graph changed signal/will need to be emitted? or is
	 * that performed by a higher level class.
	 */
	void set_graph(Graph*);

	/**
	 * Process one cycle of the engine.
	 * @return true on success, false on some error. There will probably need
	 * to be way of propagating the error.
	 *
	 * iterate will always block until the graph has been completely processed
	 * but there needs to be a way to iterate the graph as fast as possible
	 * without buffer underrun etc. The current way I'm thinking this could be
	 * achieved would be the check at the start of the cycle if all the nodes
	 * have the data they require to perform processing and if not then perform
	 * some action depending on what the requirements are. For instance if the
	 * graph is being used for exporting audio then wait for the data to become
	 * available and then continue processing. For playback of data in realtime
	 * to an audio device then perhaps declick/fade out whatever audio is in
	 * the buffers and stop transport.
	 */
	bool iterate();

private:
	// TODO Make NonCopyable
};

} // namespace mojo

#endif // MOJO_ENGINE_H
