
#ifndef GMOJO_TRACKVIEW_INCLUDED
#define GMOJO_TRACKVIEW_INCLUDED

#include <list>

#include <gtk/gtk.h>

#include <mojo/project_ptr.hpp>

#include <ui/gtk/widget.hpp>

#include <ui/track.hpp>
#include <ui/track_canvas.hpp>

namespace gmojo {

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
	TrackView (mojo::ProjectSPtr project);

	~TrackView ();

	GtkWidget* get_widget() const { return m_hpaned;}

private:

	mojo::ProjectSPtr m_project;

	GtkWidget* m_scrolled_window;
	GtkWidget* m_label;
	GtkWidget* m_hpaned;

	TrackCanvas m_canvas;

	typedef std::list<boost::shared_ptr<Track> > TrackList;

	TrackList m_track_list;

};

} // namespace gmojo

#endif
