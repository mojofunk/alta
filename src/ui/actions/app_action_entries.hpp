
#ifndef GMOJO_APP_ACTION_ENTRIES
#define GMOJO_APP_ACTION_ENTRIES

#include <glib/gi18n.h>

#include <gtk/gtk.h>

#include <ui/actions/app_actions.hpp>

namespace gmojo {

const GtkActionEntry app_action_entries[] = 
{
	{ "project-new", GTK_STOCK_NEW, NULL, "<control>N",
		N_("Create a new project"), G_CALLBACK (new_project) },

	{ "quit", GTK_STOCK_QUIT, NULL, "<control>Q",
		N_("Quit the program"), G_CALLBACK (quit) }

};

} // namespace gmojo

#endif
