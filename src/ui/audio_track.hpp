
#ifndef GMOJO_AUDIO_TRACK_INCLUDED
#define GMOJO_AUDIO_TRACK_INCLUDED

#include <ui/track_view.hpp>
#include <ui/audio_track_control.hpp>

namespace gmojo {

class AudioTrack : public Track
{
public:

	/**
	 * TrackControl an widget that gets packed into the 
	 * TrackControlList widget, different track types create 
	 * custom TrackControl derived widgets.
	 */
	virtual TrackControl* track_control() = 0;

private:

	//AudioTrack m_audio_track;
	
	AudioTrackControl m_audio_track_control;
};

} // namespace gmojo

#endif // GMOJO_AUDIO_TRACK_VIEW_INCLUDED
