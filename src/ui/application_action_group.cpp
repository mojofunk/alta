
#include <ui/application_action_group.hpp>
#include <ui/application_action_entries.hpp>

namespace gmojo {

const char* const application_action_group_name = "ApplicationActions";

GtkActionGroup*
application_action_group_new(Application* app)
{
	GtkActionGroup* action_group = gtk_action_group_new (application_action_group_name);
	
	if(!action_group)
	{
#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL;
#endif
	}
	
	//gtk_action_group_set_translation_domain (action_group, NULL);

	gtk_action_group_add_actions (action_group,
			application_action_entries,
			G_N_ELEMENTS (application_action_entries),
			app);
	
	return action_group;
}

} // namespace gmojo
