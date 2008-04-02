
#ifndef GMOJO_WIDGET_INCLUDED
#define GMOJO_WIDGET_INCLUDED

#include <gtk/gtk.h>

namespace gmojo {

class Widget
{
public: // constructors

	virtual ~Widget () { }

public: // interface

	virtual GtkWidget* get_widget () const = 0;

};

} // namespace gmojo

#endif
