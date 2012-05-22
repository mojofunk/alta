
#ifndef UI_SESSION_EVENT_HANDLER
#define UI_SESSION_EVENT_HANDLER

#include <mojo/mojo.hpp>

#include <sigc++/trackable.h>
#include <sigc++/signal.h>

#include "dispatcher.hpp"

namespace ui {

class ApplicationEventHandler : public mojo::ApplicationEventHandler
{
public: // typedefs

	typedef sigc::signal<void, mojo::Project*> project_signal_t;
	typedef sigc::signal<void, mojo::Project*, mojo::Track*> track_signal_t;
	typedef sigc::signal<void, mojo::Project*, float> transport_speed_changed_signal_t;
	typedef sigc::signal<void, mojo::Project*, mojo::count_t> transport_position_changed_signal_t;
	typedef sigc::signal<void, mojo::Project*, bool> transport_record_changed_signal_t;

public:

	ApplicationEventHandler ();
	~ApplicationEventHandler ();

public: // signal accessors

	// is it thread safe to access these signals?
	// signals are only emitted in gui thread so emission and connection
	// never occur simultaneously
	project_signal_t& signal_project_added ()
	{ return m_signal_project_added; }

	project_signal_t& signal_project_removed ()
	{ return m_signal_project_removed; }

	project_signal_t& signal_active_project_changed ()
	{ return m_signal_active_project_changed; }

	track_signal_t& signal_track_added ()
	{ return m_signal_track_added; }

	track_signal_t& signal_track_removed ()
	{ return m_signal_track_removed; }

	transport_speed_changed_signal_t& signal_transport_speed_changed ()
	{ return m_signal_transport_speed_changed; }

	transport_position_changed_signal_t& signal_transport_position_changed ()
	{ return m_signal_transport_position_changed; }

	transport_record_changed_signal_t& signal_transport_record_changed ()
	{ return m_signal_transport_record_changed; }

private: // signals

	project_signal_t m_signal_project_added;
	project_signal_t m_signal_project_removed;
	project_signal_t m_signal_active_project_changed;

	track_signal_t m_signal_track_added;
	track_signal_t m_signal_track_removed;

	transport_speed_changed_signal_t m_signal_transport_speed_changed;
	transport_position_changed_signal_t m_signal_transport_position_changed;
	transport_record_changed_signal_t m_signal_transport_record_changed;

	Dispatcher m_dispatcher;

protected:

	/*
	 * These virtual methods are part of the mojo::ApplicationEventHandler API
	 * and are called by the Application from the Application thread
	 */

	virtual void on_project_added (mojo::Project*);

	virtual void on_project_removed (mojo::Project*);

	virtual void on_project_saved (mojo::Project*);

	virtual void on_track_added (mojo::Project*, mojo::Track*);

	virtual void on_track_removed (mojo::Project*, mojo::Track*);

	virtual void on_project_property_changed(mojo::Project*, mojo::Property*);

	virtual void on_active_project_changed (mojo::Project*);

	virtual void on_track_property_changed(mojo::Project*, mojo::Track*, mojo::Property*);

	virtual void on_transport_speed_changed (mojo::Project*, float speed);

	virtual void on_transport_position_changed (mojo::Project*, mojo::count_t);

	virtual void on_transport_record_changed (mojo::Project*, bool);
};

} // namespace ui

#endif
