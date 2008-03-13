
#ifndef GMOJO_GTK_WIDGET_INCLUDED
#define GMOJO_GTK_WIDGET_INCLUDED

#include <gtk/gtk.h>

namespace gtk
{

class Widget
{
public: // constructors

	virtual ~Widget () { }

public: // interface

	virtual GtkWidget* get_widget () const = 0;

};

} // namespace gtk

#endif
