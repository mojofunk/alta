
#ifndef GMOJO_APPLICATION_ACTIONS_INCLUDED
#define GMOJO_APPLICATION_ACTIONS_INCLUDED

#include <gtk/gtkaction.h>

#include <ui/application.hpp>

namespace gmojo {

	void new_project (GtkAction*, Application*);
	
	void quit (GtkAction*, Application*);

} // namespace gmojo

#endif
