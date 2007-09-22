
#ifndef GMOJO_APPLICATION_ACTION_ENTRIES_INCLUDED
#define GMOJO_APPLICATION_ACTION_ENTRIES_INCLUDED

#include <glib/gi18n.h>

#include <gtk/gtk.h>

#include <ui/actions/application_actions.hpp>

namespace gmojo {

const GtkActionEntry application_action_entries[] = 
{
	{ "NewProject", GTK_STOCK_NEW, NULL, "<control>N",
		N_("Create a new project"), G_CALLBACK (new_project) },

	{ "Quit", GTK_STOCK_QUIT, NULL, "<control>Q",
		N_("Quit the program"), G_CALLBACK (quit) }

};

} // namespace gmojo

#endif
