
#ifndef GMOJO_TRACKVIEW_INCLUDED
#define GMOJO_TRACKVIEW_INCLUDED

#include <list>

#include <ui/gtk/widget.hpp>
#include <ui/gtk/widget_ptr.hpp>

namespace gmojo {

class Project;
class Track;

class TrackView : public gtk::Widget
{
public:

	/**
	 * EditCanvas needs to iterate through the tracks in 
	 * the project and create a new TrackView for each 
	 * track type. It also needs to connect to the track 
	 * added signal so it can create a new TrackView for
	 * any tracks that are added to the project.
	 */
	TrackView (Project* project);

	~TrackView ();

	GtkWidget* get_widget() const { return m_hpaned;}

private:

	void on_track_added (Track* track);

private:

	Project* m_project;

	GtkWidget* m_scrolled_window;
	GtkWidget* m_label;
	GtkWidget* m_hpaned;

	gtk::WidgetSPtr m_canvas;

	typedef std::list<Track*> track_container_t;

	track_container_t m_tracks; 
};

} // namespace gmojo

#endif
