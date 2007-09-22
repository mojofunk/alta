
#ifndef GMOJO_EDIT_WINDOW_ACTION_ENTRIES_INCLUDED
#define GMOJO_EDIT_WINDOW_ACTION_ENTRIES_INCLUDED

#include <glib/gi18n.h>

#include <gtk/gtk.h>

namespace gmojo {

const GtkActionEntry edit_window_menu_action_entries[] = 
{
	{ "File", NULL, N_("_File"), NULL, NULL, NULL },
	{ "Edit", NULL, N_("_Edit"), NULL, NULL, NULL },
	{ "View", NULL, N_("_View"), NULL, NULL, NULL },
	{ "Help", NULL, N_("_Help"), NULL, NULL, NULL },

	{ "Import", NULL, N_("_Import"), NULL, NULL, NULL }
};

} // namespace gmojo

#endif
