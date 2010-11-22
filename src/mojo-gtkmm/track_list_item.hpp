
#ifndef UI_TRACK_LIST_ITEM
#define UI_TRACK_LIST_ITEM

#include <inttypes.h>

#include <gtkmm/box.h>

namespace ui {

class TrackListItem : public Gtk::VBox
{
public:

	typedef sigc::signal<void> height_changed_signal_t;

public:

	virtual ~TrackListItem ();

public:

	/**
	 * A track list item may need to hide control widgets
	 * based on height
	 */
	virtual void set_height (uint32_t) = 0;

	virtual uint32_t get_height () const = 0;

	virtual void set_selected (bool) = 0;

	virtual bool get_selected () const = 0;

public: // signal_accessors

	height_changed_signal_t& signal_height_changed ()
	{ return m_signal_height_changed; }

protected:

	height_changed_signal_t m_signal_height_changed;


};

} // namespace ui

#endif
