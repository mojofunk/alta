
#ifndef UI_BUS
#define UI_BUS

#include <mojo/mojo.hpp>

#include <sigc++/trackable.h>
#include <sigc++/signal.h>

namespace ui {

class Bus : public mojo::SessionBus
{
public: // typedefs

	typedef sigc::signal<void, mojo::Track*> track_signal_t;
	typedef sigc::signal<void> transport_changed_signal_t;

public:

	Bus ();
	~Bus ();

public: // signal accessors

	track_signal_t& signal_track_added ()
	{ return m_signal_track_added; }

	track_signal_t& signal_track_removed ()
	{ return m_signal_track_removed; }

private: // signals

	track_signal_t m_signal_track_added;
	track_signal_t m_signal_track_removed;

	transport_changed_signal_t m_signal_transport_changed;

protected:

	virtual void on_project_added (mojo::Project*);

	virtual void on_project_removed (mojo::Project*);

	virtual void on_project_saved (mojo::Project*);

	virtual void on_track_added (mojo::Track*);

	virtual void on_track_removed (mojo::Track*);

};

} // namespace ui

#endif
