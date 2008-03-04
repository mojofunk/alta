#ifndef GMOJO_PROJECT_ACTION_GROUP
#define GMOJO_PROJECT_ACTION_GROUP

#include <gtk/gtk.h>

namespace gmojo {

class Project;

/**
 * The name of the action group returned by 
 * project_action_group_new
 */
extern const char* const project_action_group_name;

/**
 * @return An action group for the project instance.
 *
 * The caller holds the only reference to the action group.
 */
GtkActionGroup* project_action_group_new(Project*);

} // namespace gmojo

#endif
