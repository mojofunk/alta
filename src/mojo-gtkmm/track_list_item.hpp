
#ifndef UI_TRACK_LIST_ITEM
#define UI_TRACK_LIST_ITEM

#include <inttypes.h>

#include <gtkmm/box.h>

namespace ui {

class TrackListItem : public Gtk::VBox
{
public:

	virtual ~TrackListItem ();

public:

	virtual void set_height () = 0;

	virtual uint32_t get_height () const = 0;

	virtual void set_selected (bool) = 0;

	virtual bool get_selected () const = 0;

};

} // namespace ui

#endif
