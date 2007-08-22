
#include <ui/edit_window_menu_action_group.hpp>
#include <ui/edit_window_menu_action_entries.hpp>

namespace gmojo {

const char* const edit_window_menu_action_group_name = "EditWindowMenuActions";

GtkActionGroup*
edit_window_menu_action_group_new()
{
	GtkActionGroup* action_group =
		gtk_action_group_new (edit_window_menu_action_group_name);

	//gtk_action_group_set_translation_domain (action_group, NULL);

	// passing NULL as the last arg because there is no instance in this case
	gtk_action_group_add_actions (action_group,
			edit_window_menu_action_entries,
			G_N_ELEMENTS (edit_window_menu_action_entries),
			NULL);
	
	return action_group;
}

} // namespace gmojo
