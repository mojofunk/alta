#ifndef UI_TRACK_LIST
#define UI_TRACK_LIST

#include <gtkmm/box.h>

namespace ui {

class TrackListItem;

/**
 * The height of the items in the track list have to be exactly the
 * same size as the TrackCanvasItem. A Gtkmm::SizeGroup would be useful
 * if it worked for CanvasItems.
 */
class TrackList : public Gtk::VBox {
public:
	TrackList();

public:
	void add(TrackListItem* item);

	void remove(TrackListItem* item);

private:
	static const int s_min_width = 100;
	static const int s_min_height = 300;
};

} // namespace ui

#endif
