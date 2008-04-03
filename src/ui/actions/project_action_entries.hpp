
#ifndef GMOJO_PROJECT_ACTION_ENTRIES_INCLUDED
#define GMOJO_PROJECT_ACTION_ENTRIES_INCLUDED

#include <glib/gi18n.h>

#include <gtk/gtk.h>

#include <ui/actions/project_actions.hpp>

namespace gmojo {

const GtkActionEntry project_action_entries[] = 
{
	{ "project-save", GTK_STOCK_SAVE, NULL, "<control>S", 
		N_("Save the current project"), G_CALLBACK (save_project) },

	{ "project-close", GTK_STOCK_CLOSE, NULL, "<control>W",
		N_("Close the current project"), G_CALLBACK (close_project) },

	{ "project-new-audio-track", GTK_STOCK_NEW, NULL, "<control>A",
		N_("Create a new audio track"), G_CALLBACK (create_audio_track) },
};

} // namespace gmojo

#endif
