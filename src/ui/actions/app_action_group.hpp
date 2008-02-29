#ifndef GMOJO_APP_ACTION_GROUP
#define GMOJO_APP_ACTION_GROUP

#include <gtk/gtk.h>

#include <ui/app.hpp>

namespace gmojo {

	/**
	 * The name of the action group returned by 
	 * app_action_group_new
	 */
	extern const char* const app_action_group_name;

	/**
	 * @return An action group for the app instance.
	 *
	 * The caller holds the only reference to the action group.
	 */
	GtkActionGroup* app_action_group_new();

} // namespace gmojo

#endif
