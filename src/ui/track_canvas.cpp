#include <goocanvas.h>

#include <ui/track_canvas.hpp>

#include <ui/canvas_group.hpp>

namespace gmojo {

TrackCanvas::TrackCanvas ()
	:
		m_canvas(goo_canvas_new ())
		, m_root_item(0)
{
	m_root_item = new CanvasGroup (this);

	goo_canvas_set_root_item (GOO_CANVAS(m_canvas),
			m_root_item->get_canvas_item ());

}

TrackCanvas::~TrackCanvas ()
{


}

} // namespace gmojo
