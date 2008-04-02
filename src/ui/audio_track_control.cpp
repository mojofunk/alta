
#include <ui/audio_track_control.hpp>

namespace gmojo {

AudioTrackControl::AudioTrackControl (AudioTrack* at)
	: m_audio_track(at)
	  , m_hbox(gtk_hbox_new (FALSE, 0))
	  , m_hbuttonbox(gtk_hbutton_box_new ())
	  , m_mute_button(gtk_toggle_button_new_with_label ("M")) 
	  , m_solo_button(gtk_toggle_button_new_with_label ("S")) 
	  , m_track_name(gtk_label_new ("Track Name"))
{
	gtk_box_pack_start (GTK_BOX (m_hbuttonbox),
			m_mute_button, false, false, 0);

	gtk_box_pack_start (GTK_BOX (m_hbuttonbox),
			m_solo_button, false, false, 0);

	gtk_box_pack_start (GTK_BOX (m_hbox),
			m_hbuttonbox,
			false, false, 0);

	gtk_box_pack_start (GTK_BOX (m_hbox),
			m_track_name, false, false, 0);

	gtk_widget_show_all (m_hbox);
}

} // namespace gmojo
