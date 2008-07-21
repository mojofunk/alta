
#ifndef GMOJO_APP_ACTIONS
#define GMOJO_APP_ACTIONS

#include <gtk/gtkaction.h>

#include <ui/app.hpp>

namespace gmojo {

	void new_project (GtkAction*, App*);
	
	void quit (GtkAction*, App*);

} // namespace gmojo

#endif
