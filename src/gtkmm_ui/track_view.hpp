
#ifndef UI_TRACK_VIEW
#define UI_TRACK_VIEW

#include <list>

#include <mojo-application.hpp>

#include <gtkmm/paned.h>

#include <boost/shared_ptr.hpp>

namespace ui {

class TrackCanvas;
class TrackList;
class TrackViewItem;

/**
 * Is it a goal for the TrackList and the TrackCanvas to be independant
 * widgets and only enforce the Items in TrackCanvas and TrackList
 * to line up when in the TrackView container.
 */
class TrackView : public Gtk::HPaned {
public: // typedefs
	typedef boost::shared_ptr<TrackViewItem> TrackViewItemSPtr;
	typedef std::list<TrackViewItemSPtr> TrackViewItemList;
	typedef boost::shared_ptr<TrackCanvas> TrackCanvasPtr;
	typedef boost::shared_ptr<TrackList> TrackListPtr;

public: // constructors
	TrackView(mojo::Project* p);

	~TrackView();

private: // signal handlers
	void on_track_added_handler(mojo::Track*);

	void on_track_removed_handler(mojo::Track*);

	void on_track_added(mojo::Track*);

	void on_track_removed(mojo::Track*);

	void on_track_canvas_item_height_changed(TrackViewItemSPtr);

private: // member data
	mojo::Project* m_project;

	TrackListPtr m_track_list;

	TrackCanvasPtr m_canvas;

	TrackViewItemList m_track_view_items;
};

} // namespace ui

#endif
