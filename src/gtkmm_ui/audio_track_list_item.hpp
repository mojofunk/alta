
#ifndef UI_AUDIO_TRACK_LIST_ITEM
#define UI_AUDIO_TRACK_LIST_ITEM

#include <mojo-application.hpp>

#include <gtkmm/label.h>

#include "track_list_item.hpp"

namespace ui {

class AudioTrackListItem : public TrackListItem
{
public:

	AudioTrackListItem (mojo::Track*);

public: // TrackListItem interface

	virtual void set_height (uint32_t height);

	virtual uint32_t get_height () const;

	virtual void set_selected (bool);

	virtual bool get_selected () const;

private:

	mojo::Track* m_track;

	Gtk::Label m_track_name;

};

} // namespace ui

#endif
