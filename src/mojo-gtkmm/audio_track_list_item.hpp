
#ifndef UI_AUDIO_TRACK_LIST_ITEM
#define UI_AUDIO_TRACK_LIST_ITEM

#include <mojo/mojo.hpp>

#include <gtkmm/label.h>

#include "track_list_item.hpp"

namespace ui {

class AudioTrackListItem : public TrackListItem
{
public:

	AudioTrackListItem (mojo::Track*);

private:

	mojo::Track* m_track;

	Gtk::Label m_track_name;

};

} // namespace ui

#endif
