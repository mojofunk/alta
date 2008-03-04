
#include <ui/project.hpp>

#include <ui/app.hpp>

#include <ui/actions/project_actions.hpp>

#include <ui/dialogs/new_audio_track_dialog.hpp>

#include <iostream>

namespace gmojo {

void
save_project (GtkAction*, Project* project)
{
	project->save ();
}

void
close_project (GtkAction*, Project* project)
{
	App::close_project (project);
}

void
create_audio_track (GtkAction*, Project* project)
{
	// project->create_audio_track ();
	
	NewAudioTrackDialog dialog;

	NewAudioTrackDialog::Response response = dialog.run();

	if (response == NewAudioTrackDialog::Cancel) return;

	// new audio track dialog etc
}

}
