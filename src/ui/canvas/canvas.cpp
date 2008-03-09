#include <goocanvas.h>

#include <ui/canvas/canvas.hpp>

namespace goo {

Canvas::Canvas ()
	:
		m_canvas(goo_canvas_new ())
{

}

Canvas::~Canvas ()
{

}

} // namespace goo
