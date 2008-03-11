
#include <ui/audio_track_control.hpp>

namespace gmojo {

AudioTrackControl::AudioTrackControl (AudioTrack* at)
	:
		m_audio_track(at),
		m_label(gtk_label_new ("Track name"))
{

	gtk_widget_show (m_label);
}

} // namespace gmojo
