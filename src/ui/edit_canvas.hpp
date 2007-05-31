
#ifndef GMOJO_EDIT_CANVAS_INCLUDED
#define GMOJO_EDIT_CANVAS_INCLUDED

#include <list>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <gtk/gtk.h>
#include <goocanvas.h>

#include <libmojo/object.hpp>
#include <libmojo/project.hpp>

#include <ui/track_view.hpp>

namespace gmojo {

class EditCanvas : public mojo::Object
{
public:

	/**
	 * EditCanvas needs to iterate through the tracks in 
	 * the project and create a new TrackView for each 
	 * track type. It also needs to connect to the track 
	 * added signal so it can create a new TrackView for
	 * any tracks that are added to the project.
	 */
	EditCanvas(mojo::Project* project);

	~EditCanvas();

	GtkWidget* widget() const { return m_hpaned;}

protected:

	virtual void destroy ();

	virtual void dispose ();

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

	mojo::Project* m_project;

	GtkWidget* m_hpaned;

	GtkWidget* m_label;
	GtkWidget* m_scrolled_window;

	GtkWidget* m_canvas;

	GooCanvasItem* m_root_item;

	typedef std::list<boost::shared_ptr<TrackView> > TrackViewList;

	TrackViewList m_track_list;

};

} // namespace gmojo

#endif // GMOJO_EDIT_CANVAS_INCLUDED
