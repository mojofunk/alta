
#ifndef GMOJO_AUDIO_TRACK_CONTROL
#define GMOJO_AUDIO_TRACK_CONTROL

#include <ui/track_control.hpp>

namespace gmojo {

class AudioTrack;

class AudioTrackControl : public TrackControl
{
public: // constructors

	AudioTrackControl (AudioTrack*);

public: // widget interface

	virtual GtkWidget* get_widget() const
	{ return m_hbox; }

private: // member data

	AudioTrack* m_audio_track;

	GtkWidget* m_hbox;

	GtkWidget* m_hbuttonbox;
	GtkWidget* m_mute_button;
	GtkWidget* m_solo_button;

	GtkWidget* m_track_name;

};

} // namespace gmojo

#endif
