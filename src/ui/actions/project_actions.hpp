
#ifndef GMOJO_PROJECT_ACTIONS_INCLUDED
#define GMOJO_PROJECT_ACTIONS_INCLUDED

#include <gtk/gtkaction.h>

namespace gmojo {

	class mojo::Project;

	void save_project (GtkAction*, mojo::Project*);
	
	void close_project (GtkAction*, mojo::Project*);

	void create_audio_track (GtkAction*, mojo::Project*);

} // namespace gmojo

#endif
