
#include "track_view_item_factory.hpp"

#include "audio_track_view_item.hpp"
#include "audio_track.hpp"

//#include "midi_track_view_item.hpp"

namespace ui {

TrackViewItem*
TrackViewItemFactory::create (Track* track)
{
	AudioTrack* audio_track = dynamic_cast<AudioTrack*>(track);

	if (audio_track)
	{
		return new AudioTrackViewItem (audio_track);
	}

	return 0;
}

} // namespace ui
