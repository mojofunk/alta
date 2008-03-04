
#include <ui/project.hpp>

#include <ui/app.hpp>

#include <ui/actions/project_actions.hpp>

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
	project->create_audio_track ();
}

} // namespace gmojo
