
#include <ui/app.hpp>
#include <ui/project.hpp>
#include <ui/edit_window.hpp>
#include <ui/audio_track.hpp>

#include <ui/dialogs/new_audio_track_dialog.hpp>

namespace gmojo {

Project::Project()
{

}

Project::~Project()
{

}

void
Project::save ()
{


}

void
Project::create_audio_track ()
{
	NewAudioTrackDialog dialog;

	NewAudioTrackDialog::Response response = dialog.run();

	//if (response == NewAudioTrackDialog::Cancel) return;

	TrackSPtr at(new AudioTrack);

	if (at)
	{
		m_tracks.insert(at);
		m_signal_track_added (at.get());
	}
}

} // namespace gmojo
