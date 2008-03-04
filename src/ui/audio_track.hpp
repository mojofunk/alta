
#ifndef GMOJO_AUDIO_TRACK_INCLUDED
#define GMOJO_AUDIO_TRACK_INCLUDED

#include <ui/track.hpp>
#include <ui/audio_track_control.hpp>

namespace gmojo {

class AudioTrack : public Track
{
public:

	virtual gtk::Widget* track_control()
	{ return m_track_control.get(); }

private:
	
	gtk::WidgetSPtr m_track_control;
};

} // namespace gmojo

#endif // GMOJO_AUDIO_TRACK_VIEW_INCLUDED
