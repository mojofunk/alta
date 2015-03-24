#ifndef MOJO_APPLICATION_H
#define MOJO_APPLICATION_H

#include <string>
#include <memory>

#ifndef MOJO_APPLICATION_AMALGAMATED

#include "mojo/core/object/signals.hpp"
#include "mojo/core/modules/typedefs.hpp"
#include "mojo/core/filesystem/filesystem.hpp"

#include "mojo/archive/typedefs.hpp"
#include "mojo/audio_driver/typedefs.hpp"
#include "mojo/audio_effect/typedefs.hpp"
#include "mojo/audio_file/typedefs.hpp"

#include "typedefs.hpp"
#include "types.hpp"

#endif

namespace mojo {

/**
 * If access to the worker thread is through the application and all Object classes
 * use the worker thread then changes to the Application class will cause a total
 * recompile. Better to have a singleton WorkerThread that accessed through a private
 * header.
 *
 * The application state is stored in a separate file to the project and contains
 * nothing project specific.
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
 * Should be a separate thread/context for handling state changes and reading
 * audio/midi data off disk. Group of worker threads?
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
 * Perhaps it would simplify things greatly if all objects are managed
 * by the Application or once a class is added to a project then the project
 * then manages the child class.
 *
 * This means that clients can treat any objects that are created through the
 * application as managed but do not participate in that management.
 *
 * All the internal class types contained in the Project must only be
 * accessed/referenced by the application. This makes it much easier to ensure
 * that only one thread modifies the objects.
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
 */
class Application
{
public:

	static bool initialize ();

	static void deinitialize ();

public:

	static Application& get_instance ();

	static void iteration (bool block);

public: // public API

	/**
	 * Create a new project.
	 * Async
	 */
	static void new_project ();

	/**
	 * If the native samplerate of the project
	 * and the rate of the AudioDevice are different
	 * then the audio device is re-opened to match
	 * the native rate.
	 *
	 * Async
	 */
	static void open_project (const std::string& project_file);

	/**
	 * Async
	 */
	static void save_project_as (Project*, const std::string& filename);

	/**
	 * Will send an error to the application event_handler if the if
	 * project file name hasn't been set
	 *
	 * Async
	 */
	static void save_project (Project*);

	/**
	 * should return status
	 * Async
	 */
	static void close_project (Project*);

	/**
	 * Set the project as the current active project.
	 * There can only be one active project per Application.
	 *
	 * Setting the project active unloads the current active project if
	 * there is one and then loads the current project into the engine.
	 *
	 * Async
	 */
	static void set_active_project (Project*);

	/**
	 * Get the current active project
	 *
	 * Sync...could this be a problem?
	 */
	static Project* get_active_project ();

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
	static void add_track (Project*, const TrackOptions&);

	/**
	 * Async
	 */
	static void remove_track (Project*, Track*);

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

public: // signals

	using ProjectAddedASyncSignal = signals::signal<void (Project*)>;
	using ProjectRemovedSyncSignal = signals::signal<void (Project*)>;
	using ProjectAddedFunc = ProjectAddedASyncSignal::slot_type;
	using ProjectRemovedFunc = ProjectRemovedSyncSignal::slot_type;

	static signals::connection connect_project_added (const ProjectAddedFunc& slot);

	static signals::connection connect_project_removed (const ProjectAddedFunc& slot);

public: // modules

	static AudioFileSP open_audiofile (const fs::path& p);

	static ModuleSPSet get_modules ();

	static AudioFileModuleSPSet get_audiofile_modules ();

	static AudioDriverModuleSPSet get_audio_driver_modules ();

	static AudioEffectModuleSPSet get_audio_effect_modules ();

	static ArchiveModuleSPSet get_archive_modules ();

	static ArchiveSP create_archive ();

private: // ctors

	Application ();

	~Application ();

	std::unique_ptr<internal::ApplicationData> data;

	void register_types ();

	void new_project_internal ();
	void open_project_internal (const std::string&);
	void close_project_internal (Project*);
	void set_active_project_internal (Project*);

	void add_track_internal (Project*, const TrackOptions&);
	void remove_track_internal (Project*, Track*);

};

} // namespace mojo

#endif // MOJO_APPLICATION_H
