
#include <ui/project_actions.hpp>

namespace gmojo {

void
save_project (GtkAction*, mojo::Project* project)
{


}

void
close_project (GtkAction*, mojo::Project* project)
{
	project->close();

}


}
