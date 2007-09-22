
#include <ui/actions/app_action_group.hpp>
#include <ui/actions/app_action_entries.hpp>

namespace gmojo {

const char* const app_action_group_name = "AppActions";

GtkActionGroup*
app_action_group_new(App* app)
{
	GtkActionGroup* action_group = gtk_action_group_new (app_action_group_name);
	
	//gtk_action_group_set_translation_domain (action_group, NULL);

	gtk_action_group_add_actions (action_group,
			app_action_entries,
			G_N_ELEMENTS (app_action_entries),
			app);
	
	return action_group;
}

} // namespace gmojo
