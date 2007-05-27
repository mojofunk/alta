
#ifndef GMOJO_EDIT_WINDOW_MENU_ACTION_GROUP
#define GMOJO_EDIT_WINDOW_MENU_ACTION_GROUP

#include <gtk/gtk.h>

namespace gmojo {

	/**
	 * The name of the action group returned by 
	 * edit_menu_action_group_new
	 */
	extern const char* const edit_window_menu_action_group_name;

	/**
	 * @return An action group for the top level menu items
	 * such as File, Edit, View, Help etc
	 *
	 * The caller holds the only reference to the action group.
	 */
	GtkActionGroup* edit_window_menu_action_group_new();

} // namespace gmojo

#endif
