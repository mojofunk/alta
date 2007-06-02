
#include <ui/project_actions.hpp>

namespace gmojo {

void
save_project (GtkAction*, mojo::Project* project)
{
	project->save ();

}

void
close_project (GtkAction*, mojo::Project* project)
{
	project->close ();

}


}
