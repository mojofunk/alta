
#ifndef GMOJO_EDIT_WINDOW_ACTION_ENTRIES_INCLUDED
#define GMOJO_EDIT_WINDOW_ACTION_ENTRIES_INCLUDED

#include <glib/gi18n.h>

#include <gtk/gtk.h>

namespace gmojo {

const GtkActionEntry edit_window_menu_action_entries[] = 
{
	{ "file-menu", NULL, N_("_File"), NULL, NULL, NULL },
	{ "edit-menu", NULL, N_("_Edit"), NULL, NULL, NULL },
	{ "project-menu", NULL, N_("_Project"), NULL, NULL, NULL },
	{ "view-menu", NULL, N_("_View"), NULL, NULL, NULL },
	{ "help-menu", NULL, N_("_Help"), NULL, NULL, NULL },

	{ "import-menu", NULL, N_("_Import"), NULL, NULL, NULL }
};

} // namespace gmojo

#endif
