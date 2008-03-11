
#ifndef GMOJO_AUDIO_TRACK_CONTROL_INCLUDED
#define GMOJO_AUDIO_TRACK_CONTROL_INCLUDED

#include <ui/track_control.hpp>

#include <ui/gtk/widget_ptr.hpp>

namespace gmojo {

class AudioTrack;

class AudioTrackControl : public TrackControl
{
public:

	AudioTrackControl (AudioTrack*);

public:

	virtual GtkWidget* get_widget() const
	{ return m_label; }

private:

	AudioTrack* m_audio_track;

	GtkWidget* m_label;

};

} // namespace gmojo

#endif
