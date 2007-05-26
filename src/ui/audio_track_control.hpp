
#ifndef GMOJO_AUDIO_TRACK_CONTROL_INCLUDED
#define GMOJO_AUDIO_TRACK_CONTROL_INCLUDED

#include <gtk/gtk.h>

#include <ui/track_control.hpp>

namespace gmojo {

class AudioTrackControl : TrackControl
{
public:

	//AudioTrackControl(mojo::AudioTrack audio_track);

	/**
	 * The widget that gets packed into the TrackControlList
	 */
	virtual GtkWidget* widget() { return m_base_widget; }

private:

	/**
	 * Ideally the widgets that make up the audio track controls
	 * would be loaded from a glade file.
	 */
	GtkWidget* m_base_widget;

};

} // namespace gmojo

#endif // GMOJO_AUDIO_TRACK_CONTROL_INCLUDED
