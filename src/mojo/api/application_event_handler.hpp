#ifndef MOJO_APPLICATION_EVENT_HANDLER
#define MOJO_APPLICATION_EVENT_HANDLER

#include "types.hpp"
#include "forward.hpp"

namespace mojo {

/**
 * The ApplicationEventHandler interface is how the Application communicates
 * with clients.
 *
 * The virtual calls are made by the Application in the
 * Application thread. If the events must be processed by
 * another thread(say the GUI thread) then it is up to
 * the derived class to queue the events to be processed
 * by another thread.
 *
 * Another option to virtual methods and inheritance would be to
 * Have a ApplicationEvent class and then different events from that
 * class. The clients would then just register callbacks for different
 * event types. Some possible advantages of an interface is that
 * all events have to be handled anyway so just enforce it rather than
 * having to register callbacks and then check that they have been registered
 * etc.
 * The main disadvantage is that the client code has to have a top down
 * event processing heirarchy. I think it would be better to have
 * A virtual ApplicationEvent class and Subclasses for different event types
 *
 */
class ApplicationEventHandler
{
public:

	ApplicationEventHandler();
	virtual ~ApplicationEventHandler();

protected:

	friend class Application;

	// all the events are called from the application thread

	virtual void on_project_added (Project*) = 0;

	/**
	 * Project* handle will only remain valid until
	 * end of call.
	 */
	virtual void on_project_removed (Project*) = 0;

	/*
	 * This could be a property of the project
	 */
	virtual void on_project_saved (Project*) = 0;

	virtual void on_track_added (Project*, Track*) = 0;

	virtual void on_track_removed (Project*, Track*) = 0;

	/**
	 * There needs to be a way to listen to changes
	 * in properties but as the types are opaque to the
	 * client a separate function is required for each
	 * type which is not ideal
	 */
	virtual void on_project_property_changed (Project*, Property* ) = 0;

	virtual void on_active_project_changed (Project*) = 0;

	virtual void on_track_property_changed (Project*, Track*, Property*) = 0;

	virtual void on_transport_speed_changed (Project*, float speed) = 0;

	virtual void on_transport_position_changed (Project*, count_t) = 0;

	virtual void on_transport_record_changed (Project*, bool) = 0;

};

} // namespace mojo

#endif
