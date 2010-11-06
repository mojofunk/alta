
#ifndef MOJO_SESSION
#define MOJO_SESSION

#include <string>

#include "forward.hpp"
#include "types.hpp"

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
 * The Session thread also dispatches events to the session event handler. The
 * session event handler is how the clients recieve all asyncronous messages.
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
 * All the internal class types contained in the Project must only be
 * accessed/referenced by the session. This makes it much easier to ensure
 * that only one thread modifies the objects.
 *
 * To ensure this the clients don't have direct access to the class definitions
 *
 * The Session may need to use an internal SessionEventHandler to syncronize the states of the
 * Project and the Engine.
 *
 * The Engine does not reference the Project. The Session negotiates communication
 * between the Engine and the Project.
 *
 * The Engine runs in a different context/thread than the Session(SessionDispatcher)
 *
 */
class Session
{
public: // ctors

	Session ();

	~Session ();

public: // public API

	/*
	 * Sync
	 */
	void add_event_handler (SessionEventHandler*);

	/*
	 * Sync
	 */
	void remove_event_handler (SessionEventHandler*);

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
	void save_project_as (Project*, const std::string& filename);

	/**
	 * Will send an error to the session event_handler if the if
	 * project file name hasn't been set
	 *
	 * Async
	 */
	void save_project (Project*);

	/**
	 * should return status
	 * Async
	 */
	void close_project (Project*);

	/**
	 * Set the project as the current active project.
	 * There can only be one active project per Session.
	 *
	 * Setting the project active unloads the current active project if
	 * there is one and then loads the current project into the engine.
	 *
	 * Async
	 */
	void set_active_project (Project*);

	/**
	 * Get the current active project
	 *
	 * Sync...could this be a problem?
	 */
	Project* get_active_project () const;

	/**
	 * A client should only need to request tracks when a
	 * project has been created or opened. The track_added
	 * and track_removed signals should be used by the client
	 * to maintain the list of tracks for a Project*
	 *
	 * Sync
	 *
	 * This should be a more general mechanism to get properties
	 *
	 */
	//void get_tracks (Project*, std::set<Track*>);

	/**
	 *
	 * Async
	 */
	void add_track (Project*, const TrackOptions&);

	/**
	 * Async
	 */
	void remove_track (Project*, Track*);

	static bool is_audio_track (Track*);

public: // transport API

	void transport_set_speed (float speed);
	float transport_get_speed ();

	void transport_stop ();
	void transport_play ();

	void transport_set_position (count_t pos);
	count_t transport_get_position ();

	void transport_set_record (bool record);
	bool transport_get_record ();

private:

	internal::SessionData *data;

	void add_event_handler_internal (SessionEventHandler*);
	void remove_event_handler_internal (SessionEventHandler*);

	void new_project_internal ();
	void open_project_internal (const std::string&);
	void close_project_internal (Project*);
	void set_active_project_internal (Project*);

	void add_track_internal (Project*, const TrackOptions&);
	void remove_track_internal (Project*, Track*);

	void transport_set_speed_internal (float);
	void transport_set_position_internal (count_t pos);
	void transport_set_record_internal (bool);
};

} // namespace mojo

#endif
