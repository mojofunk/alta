
#ifndef UI_TRACK_VIEW
#define UI_TRACK_VIEW

#include <list>

#include <gtkmm/paned.h>
#include <gtkmm/scrolledwindow.h>

#include <boost/shared_ptr.hpp>

namespace ui {

class Project;
class Track;
class TrackCanvas;
class TrackViewItem;

class TrackView : public Gtk::HPaned
{
public: // typedefs

	typedef boost::shared_ptr<TrackViewItem> TrackViewItemSPtr;
	typedef std::list<TrackViewItemSPtr>     TrackViewItemList;
	typedef boost::shared_ptr<TrackCanvas>   TrackCanvasPtr;

public: // constructors

	TrackView (Project* p);

	~TrackView ();

private: // signal handlers

	void on_track_added (Track*);

	void on_track_removed (Track*);

private: // member data

	Project*                m_project;

	TrackCanvasPtr          m_canvas;

	Gtk::ScrolledWindow     m_scrolled_window;
	
	TrackViewItemList       m_track_view_items;

};

} // namespace ui

#endif
