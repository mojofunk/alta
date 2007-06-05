#include <goocanvas.h>

#include <ui/goo/canvas.hpp>

#include <ui/debug/debug.hpp>

namespace goo {

Canvas::Canvas ()
	: m_canvas(goo_canvas_new ())
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

Canvas::~Canvas ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

} // namespace goo
