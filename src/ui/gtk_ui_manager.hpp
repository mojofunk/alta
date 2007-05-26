
#ifndef GTK_UI_MANAGER_INCLUDED
#define GTK_UI_MANAGER_INCLUDED

#include <gtk/gtk.h>

#include <boost/intrusive_ptr.hpp>

#include <ui/gobject_intrusive_ptr.hpp>

namespace gtk {

	boost::intrusive_ptr<GtkUIManager> ui_manager_factory();

};

#endif
