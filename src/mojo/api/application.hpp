
#ifndef MOJO_APPLICATION
#define MOJO_APPLICATION

#include <string>

#include "forward.hpp"
#include "types.hpp"

namespace mojo {

/**
 * The application class is the public API of libmojo. All interaction with a
 * project must be done through the application. This is to ensure that the state
 * of the project is modified by a single thread. None of the project classes
 * are exposed by application.
 *
 * The application state is stored in a separate file to the project and contains
 * nothing project specific.
 *
 * I think it is important to keep locking and syncronization as simple and
 * as centralized as possible.
 *
 * A application manages a task thread that asyncronously runs all tasks that
 * have been queued. some of these tasks are:
 *
 * The Application "task" thread is the only thread that makes modifications
 * to the project data structures.
 *
 * Saving the project should probably happen in a separate thread as it may
 * take some time. That should be ok though as the property data are all copied
 * from the project classes.
 *
 * Order of task thread processing
 *
 * Process queued "tasks"(Modifications to the project/etc)
 * Process Engine Events
 *  - Read data from disk and fill the playback buffers
 *  - Write data from record buffers to disk
 * Queue project to be saved if modified.
 * Dispatch Application events
 *
 * The Application thread also dispatches events to the application event handler. The
 * application event handler is how the clients recieve all asyncronous messages.
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
 * by the Application or at least creation and destruction of objects is controlled
 * through the Application.
 *
 * This means that clients can treat any objects that are created through the
 * application as managed but do not participate in that management.
 *
 * All the internal class types contained in the Project must only be
 * accessed/referenced by the application. This makes it much easier to ensure
 * that only one thread modifies the objects.
 *
 * To ensure this the clients don't have direct access to the class definitions?
 *
 * The Application may need to use an internal ApplicationEventHandler to syncronize the states of the
 * Project and the Engine.
 *
 * The Engine does not reference the Project. The Application negotiates communication
 * between the Engine and the Project.
 *
 * The Engine runs in a different context/thread than the Application(ApplicationDispatcher)
 *
 * Should only be one Application class per process so makes sense to make all methods
 * static(might as well be a C API...)
 *
 * If the worker context is exposed in a private header(perhaps in core) then the clients should
 * be able to access the project class directly and the classes can then defer some/all modification
 * calls to the worker thread.
 *
 * The main difference between the Async communication in Ardour and this library is that
 * all signals are proxied through a single class rather than signal templates.
 *
 */
class Application
{
public: // ctors

	Application ();

	~Application ();

public: // public API

	/*
	 * Sync
	 */
	void add_event_handler (ApplicationEventHandler*);

	/*
	 * Sync
	 */
	void remove_event_handler (ApplicationEventHandler*);

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
	 * Will send an error to the application event_handler if the if
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
	 * There can only be one active project per Application.
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

	/**
	 * task_t is an identifier for a particular task
	 *
	 * The task_t can be used to discover the status of task,
	 * cancel a task etc.
	 *
	 * import options:
	 *
	 * copy files to audio folder
	 * split multi-channel files into mono files
	 *
	 * The files are added to the project that is active for the application
	 *
	 */
	//task_t import_audiofiles (const paths& files, const ImportOptions&)

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

	internal::ApplicationData *data;

	void add_event_handler_internal (ApplicationEventHandler*);
	void remove_event_handler_internal (ApplicationEventHandler*);

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
