
#include <ui/actions/project_action_group.hpp>
#include <ui/actions/project_action_entries.hpp>

namespace gmojo {

const char* const project_action_group_name = "ProjectActions";

GtkActionGroup*
project_action_group_new(mojo::Project* project)
{
	GtkActionGroup* action_group = gtk_action_group_new (project_action_group_name);
	
	//gtk_action_group_set_translation_domain (action_group, NULL);

	gtk_action_group_add_actions (action_group,
			project_action_entries,
			G_N_ELEMENTS (project_action_entries),
			project);
	
	return action_group;
}

} // namespace gmojo
