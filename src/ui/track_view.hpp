
#ifndef GMOJO_TRACKVIEW_INCLUDED
#define GMOJO_TRACKVIEW_INCLUDED

#include <list>

#include <gtk/gtk.h>
#include <goocanvas.h>

#include <mojo/object.hpp>
#include <mojo/project.hpp>

#include <ui/track.hpp>

namespace gmojo {

class TrackView
{
public:

	/**
	 * EditCanvas needs to iterate through the tracks in 
	 * the project and create a new TrackView for each 
	 * track type. It also needs to connect to the track 
	 * added signal so it can create a new TrackView for
	 * any tracks that are added to the project.
	 */
	TrackView (mojo::Project::ptr project);

	~TrackView ();

	GtkWidget* widget() const { return m_hpaned;}

private:

	bool create_scrolled_window ();

	bool create_canvas ();

	bool create_track_control_list ();
	
	bool create_packing_widgets ();

	void pack_widgets ();

	void connect_signals ();

private:

	static gboolean public_on_root_button_press (GooCanvasItem  *view,
			GooCanvasItem  *target,
			GdkEventButton *event,
			gpointer        data);

	bool on_root_button_press (GooCanvasItem  *view,
			GooCanvasItem  *target,
			GdkEventButton *event);

private:

	mojo::Project::ptr m_project;

	GtkWidget* m_hpaned;

	GtkWidget* m_label;
	GtkWidget* m_scrolled_window;

	GtkWidget* m_canvas;

	GooCanvasItem* m_root_item;

	typedef std::list<boost::shared_ptr<Track> > TrackList;

	TrackList m_track_list;

};

} // namespace gmojo

#endif
