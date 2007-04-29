
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <boost/noncopyable.hpp>

#include <gtk/gtk.h>
#include <goocanvas.h>

#include <libmojo/project.hpp>

namespace gmojo {

class EditWindow : boost::noncopyable
{
public:

	EditWindow(mojo::project project);

	~EditWindow();

private:

	mojo::project m_project;

	GtkWidget* m_edit_window;
	GtkWidget* m_scrolled_window;

	GtkWidget* m_canvas;

	GooCanvasItem* m_root_item;
	GooCanvasItem* m_rect_item;
	GooCanvasItem* m_text_item;
};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
