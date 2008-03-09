
#ifndef GMOJO_TRACKVIEW_INCLUDED
#define GMOJO_TRACKVIEW_INCLUDED

#include <list>

#include <ui/gtk/widget.hpp>
#include <ui/gtk/widget_ptr.hpp>

#include <ui/track_view_item.hpp>

namespace gmojo {

class Project;
class Track;

/**
 * It maintains the height by sharing a GtkAdjustment between the
 * TrackControls and the TrackCanvasItem...? or the TrackViewItem
 * class contains the TrackControl and TrackCanvasItem for a Track
 * calling TrackViewItem::set_height resizes the TrackControl
 * and TrackCanvasItem
 *
 * The position of a Track should be able to be changed by the 
 * TrackControlList and the TrackCanvas having a reference to the
 * same TrackOrder class.
 */
class TrackView : public gtk::Widget
{
public:

	TrackView (Project* project);

	~TrackView ();

	GtkWidget* get_widget() const { return m_hpaned;}

private:

	void on_track_added (Track*);

	void on_track_removed (Track*);

	static TrackViewItem* create_track_view_item (Track*);

private:

	Project* m_project;

	GtkWidget* m_scrolled_window;
	GtkWidget* m_label;
	GtkWidget* m_hpaned;

	gtk::WidgetSPtr m_canvas;

	typedef std::list<TrackViewItem*> track_view_items_t;

	track_view_items_t m_track_views; 
};

} // namespace gmojo

#endif
