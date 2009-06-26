#ifndef UI_TRACK_LIST
#define UI_TRACK_LIST

#include <gtkmm/box.h>

namespace ui {

class TrackListItem;

class TrackList : public Gtk::VBox
{
public:

	TrackList ();

public:

	void add (TrackListItem* item);

	void remove (TrackListItem* item);

private:

};

} // namespace ui

#endif
