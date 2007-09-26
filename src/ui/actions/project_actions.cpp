
#include <mojo/project.hpp>

#include <ui/actions/project_actions.hpp>

#include <ui/dialogs/new_audio_track_dialog.hpp>

#include <iostream>

namespace gmojo {

void
save_project (GtkAction*, mojo::Project* project)
{

	try
	{
		project->save ();
	}
	catch(...)
	{
	    std::cerr << "blah" << std::endl;

	}

	// else call gmojo::save_project_as

	// must get a directory to save/move project to
	// a ProjectFormat and a project file name

#if 0
	const fs::path dir("./");

	mojo::project_format_ptr mojo_format(new mojo::MojoProjectFormat);

	try
	{
		project->save_as (mojo_format, dir, "Untitled");
	}
	catch(...)
	{

	}
#endif

}

void
close_project (GtkAction*, mojo::Project* project)
{
	project->close ();
}

void
create_audio_track (GtkAction*, mojo::Project* project)
{
	NewAudioTrackDialog dialog;

	NewAudioTrackDialog::Response response = dialog.run();

	if (response == NewAudioTrackDialog::Cancel) return;

	// new audio track dialog etc
}

}
