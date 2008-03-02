
#ifndef GMOJO_GOO_CANVAS_INCLUDED
#define GMOJO_GOO_CANVAS_INCLUDED

#include <ui/gtk/widget.hpp>

namespace goo {

class Canvas : public gtk::Widget
{
public:

	Canvas ();

	virtual ~Canvas ();

	GtkWidget* get_widget () const
	{ return m_canvas; }

protected:

	GtkWidget* m_canvas;

};

}

#endif
