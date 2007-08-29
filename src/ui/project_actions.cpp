
#include <mojo/project_format.hpp>
#include <mojo/mojo_project_format.hpp>

#include <ui/project_actions.hpp>

#include <ui/dialogs/new_audio_track_dialog.hpp>

namespace gmojo {

void
save_project (GtkAction*, mojo::Project* project)
{

	// don't rely on this, just try to save and catch
	// no_format_exception or something and call save_project_as
	mojo::project_format_ptr format = project->format ();

	if(format)
	{
		try
		{
			project->save ();
		}
		catch(...)
		{

		}

		return;
	}
	
	// else call gmojo::save_project_as

	// must get a directory to save/move project to
	// a ProjectFormat and a project file name

	const fs::path dir("./");

	mojo::project_format_ptr mojo_format(new mojo::MojoProjectFormat);

	try
	{
		project->save_as (mojo_format, dir, "Untitled");
	}
	catch(...)
	{

	}
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
