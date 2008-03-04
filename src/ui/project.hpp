
#ifndef GMOJO_PROJECT_INCLUDED
#define GMOJO_PROJECT_INCLUDED

#include <set>

#include <boost/signal.hpp>

#include <ui/gtk/window_ptr.hpp>

#include <ui/track_ptr.hpp>

namespace gmojo {

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed. It also 
   manages the top level windows for a project
*/
class Project
{
public:

	typedef boost::signal<void (Track*)> track_signal_t;

public:

	Project ();

	~Project ();

public:

	void save ();

	void create_audio_track ();

public:

	track_signal_t& track_added_signal () { return m_signal_track_added; }

private:

	bool on_edit_window_delete_event ();

private:

	// per project windows

	gtk::WindowSPtr m_edit_window;

private: // signals

	track_signal_t m_signal_track_added;
	track_signal_t m_signal_track_removed;

private:

	typedef std::set<TrackSPtr> track_container_t;

	track_container_t m_tracks;

};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
