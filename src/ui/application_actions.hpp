
#ifndef GMOJO_APPLICATION_ACTIONS_INCLUDED
#define GMOJO_APPLICATION_ACTIONS_INCLUDED

#include <glib/gi18n.h>

#include <gtk/gtk.h>

#include <ui/application_commands.hpp>

namespace gmojo {

const GtkActionEntry application_action_entries[] = 
{
	// Top level
	{ "File", NULL, N_("_File"), NULL, NULL, NULL },

	// File menu
	{ "FileNew", GTK_STOCK_NEW, NULL, "<control>N",
		N_("Create a new document"), G_CALLBACK (file_new) }

};

} // namespace gmojo

#endif
