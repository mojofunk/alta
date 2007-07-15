
#include <mojo/project_format.hpp>
#include <mojo/mojo_project_format.hpp>

#include <ui/project_actions.hpp>

#include <ui/dialogs/new_audio_track_dialog.hpp>

namespace gmojo {

void
save_project (GtkAction*, mojo::Project* project)
{

	mojo::ProjectFormat::ptr format = project->format ();

	if(format)
	{
		try
		{
			project->save ();
		}
		catch(...)
		{

#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL;
#endif

		}

		return;
	}
	// else save_as

	// must get a directory to save/move project to
	// a ProjectFormat and a project file name

	const fs::path dir("./");

	mojo::MojoProjectFormat::ptr mojo_format(new mojo::MojoProjectFormat);

	try
	{
		project->save_as (mojo_format, dir, "Untitled");
	}
	catch(...)
	{

#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL;
#endif

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
#ifdef GMOJO_DEBUG_EXTRA
		LOG_GMOJO_DEBUG;
#endif

	NewAudioTrackDialog dialog;

	NewAudioTrackDialog::Response response = dialog.run();

	if (response == NewAudioTrackDialog::Cancel) return;

	// new audio track dialog etc

}

}
