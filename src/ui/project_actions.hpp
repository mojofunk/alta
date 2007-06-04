
#ifndef GMOJO_PROJECT_ACTIONS_INCLUDED
#define GMOJO_PROJECT_ACTIONS_INCLUDED

#include <gtk/gtkaction.h>

#include <mojo/project.hpp>

namespace gmojo {

	void save_project (GtkAction*, mojo::Project*);
	
	void close_project (GtkAction*, mojo::Project*);

} // namespace gmojo

#endif
