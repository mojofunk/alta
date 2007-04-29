
#ifndef GMOJO_EDIT_CANVAS_INCLUDED
#define GMOJO_EDIT_CANVAS_INCLUDED

#include <boost/noncopyable.hpp>

#include <gtk/gtk.h>
#include <goocanvas.h>

#include <libmojo/project.hpp>

namespace gmojo {

class EditCanvas : boost::noncopyable
{
public:

	EditCanvas(mojo::project project);

	~EditCanvas();

	GtkWidget* widget() const { return m_scrolled_window;}

private:

	mojo::project m_project;

	GtkWidget* m_scrolled_window;

	GtkWidget* m_canvas;

	GooCanvasItem* m_root_item;
	GooCanvasItem* m_rect_item;
	GooCanvasItem* m_text_item;
};

} // namespace gmojo

#endif // GMOJO_EDIT_CANVAS_INCLUDED
