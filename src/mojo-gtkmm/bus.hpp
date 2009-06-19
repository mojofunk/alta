
#ifndef UI_BUS
#define UI_BUS

#include <mojo/mojo.hpp>

#include <sigc++/trackable.h>
#include <sigc++/signal.h>

#include "dispatcher.hpp"

namespace ui {

class Bus : public mojo::SessionBus
{
public: // typedefs

	typedef sigc::signal<void, mojo::Project*> project_signal_t;
	typedef sigc::signal<void, mojo::Project*, mojo::Track*> track_signal_t;
	typedef sigc::signal<void> transport_changed_signal_t;

public:

	Bus ();
	~Bus ();

public: // signal accessors

	project_signal_t& signal_project_added ()
	{ return m_signal_project_added; }

	project_signal_t& signal_project_removed ()
	{ return m_signal_project_removed; }

	track_signal_t& signal_track_added ()
	{ return m_signal_track_added; }

	track_signal_t& signal_track_removed ()
	{ return m_signal_track_removed; }

private: // signals

	project_signal_t m_signal_project_added;
	project_signal_t m_signal_project_removed;

	track_signal_t m_signal_track_added;
	track_signal_t m_signal_track_removed;

	transport_changed_signal_t m_signal_transport_changed;

	Dispatcher m_dispatcher;

protected:

	virtual void on_project_added (mojo::Project*);

	virtual void on_project_removed (mojo::Project*);

	virtual void on_project_saved (mojo::Project*);

	virtual void on_track_added (mojo::Project*, mojo::Track*);

	virtual void on_track_removed (mojo::Project*, mojo::Track*);

	virtual void on_project_property_changed(mojo::Project*, mojo::Property*);

	virtual void on_track_property_changed(mojo::Project*, mojo::Track*, mojo::Property*);

};

} // namespace ui

#endif
