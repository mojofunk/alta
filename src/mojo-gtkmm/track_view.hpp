
#ifndef UI_TRACK_VIEW
#define UI_TRACK_VIEW

#include <list>

#include <mojo/mojo.hpp>

#include <gtkmm/paned.h>

#include <boost/shared_ptr.hpp>

namespace ui {

class TrackCanvas;
class TrackList;
class TrackViewItem;

class TrackView : public Gtk::HPaned
{
public: // typedefs

	typedef boost::shared_ptr<TrackViewItem> TrackViewItemSPtr;
	typedef std::list<TrackViewItemSPtr>     TrackViewItemList;
	typedef boost::shared_ptr<TrackCanvas>   TrackCanvasPtr;
	typedef boost::shared_ptr<TrackList>     TrackListPtr;

public: // constructors

	TrackView (mojo::Project* p);

	~TrackView ();

private: // signal handlers

	void on_track_added (mojo::Track*);

	void on_track_removed (mojo::Track*);

private: // member data

	mojo::Project*          m_project;

	TrackCanvasPtr          m_canvas;

	TrackListPtr            m_track_list;
	
	TrackViewItemList       m_track_view_items;

};

} // namespace ui

#endif
