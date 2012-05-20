
#include "track_view_item_factory.hpp"

#include "audio_track_view_item.hpp"

//#include "midi_track_view_item.hpp"

namespace ui {

TrackViewItem*
TrackViewItemFactory::create (mojo::Track* track)
{
	if (mojo::Session::is_audio_track (track))
	{
		return new AudioTrackViewItem (track);
	}
	return 0;
}

} // namespace ui
