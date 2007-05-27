#ifndef GMOJO_APPLICATION_ACTION_GROUP
#define GMOJO_APPLICATION_ACTION_GROUP

#include <gtk/gtk.h>

#include <ui/application.hpp>

namespace gmojo {

	/**
	 * The name of the action group returned by 
	 * application_action_group_new
	 */
	extern const char* const application_action_group_name;

	/**
	 * @return An action group for the application instance.
	 *
	 * The caller holds the only reference to the action group.
	 */
	GtkActionGroup* application_action_group_new(Application*);

} // namespace gmojo

#endif
