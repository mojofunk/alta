
#ifndef GMOJO_GOO_CANVAS_INCLUDED
#define GMOJO_GOO_CANVAS_INCLUDED

#include <gtk/gtkwidget.h>

namespace goo {

class Canvas {
public:

	Canvas ();

	virtual ~Canvas ();

	GtkWidget* widget ()
	{ return m_canvas; }

protected:

	GtkWidget* m_canvas;


};

}

#endif
