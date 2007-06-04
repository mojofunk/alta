
#include <mojo/project_format.hpp>
#include <mojo/mojo_project_format.hpp>

#include <ui/project_actions.hpp>

namespace gmojo {

void
save_project (GtkAction*, mojo::Project* project)
{

	mojo::ProjectFormat* format = project->format ();

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

	mojo::MojoProjectFormat* mojo_format = new mojo::MojoProjectFormat;

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

	mojo_format->unref ();

}

void
close_project (GtkAction*, mojo::Project* project)
{
	project->close ();

}


}
