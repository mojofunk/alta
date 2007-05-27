
#ifndef GMOJO_AUDIO_TRACK_VIEW_INCLUDED
#define GMOJO_AUDIO_TRACK_VIEW_INCLUDED

#include <ui/track_view.hpp>
#include <ui/audio_track_control.hpp>

namespace gmojo {

/**
 * Is TrackView an appropriate name? there could be an
 * argument for calling the widget that contains all the tracks
 * the TrackView.
 */

/**
 * TrackView is an interface that all Track types
 * derive from. This is so the EditCanvas doesn't need to know
 * about specific track types.
 */
class AudioTrackView : public TrackView
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
