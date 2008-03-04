
#ifndef GMOJO_PROJECT_ACTIONS_INCLUDED
#define GMOJO_PROJECT_ACTIONS_INCLUDED

#include <gtk/gtkaction.h>

namespace gmojo {

class Project;

void save_project (GtkAction*, Project*);

void close_project (GtkAction*, Project*);

void create_audio_track (GtkAction*, Project*);

} // namespace gmojo

#endif
