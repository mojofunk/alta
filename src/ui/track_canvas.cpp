#include <goocanvas.h>

#include <ui/track_canvas.hpp>

#include <ui/canvas_group.hpp>

#include <ui/tools/object_selection_tool.hpp>

namespace gmojo {

TrackCanvas::TrackCanvas ()
	:
		m_canvas(goo_canvas_new ())
		, m_root_item(0)
		, m_tool(new ObjectSelectionTool) // leak
{
	m_root_item = new CanvasGroup (this);

	goo_canvas_set_root_item (GOO_CANVAS(m_canvas),
			m_root_item->get_canvas_item ());

}

TrackCanvas::~TrackCanvas ()
{


}

bool
TrackCanvas::on_button_press_event (CanvasItem* i, GdkEventButton* ev)
{
	return m_tool->on_button_press (this, i, ev);
}

bool
TrackCanvas::on_button_release_event (CanvasItem* i, GdkEventButton* ev)
{
	return m_tool->on_button_release (this, i, ev);
}

bool
TrackCanvas::on_motion_notify_event (CanvasItem* i, GdkEventMotion* ev)
{
	return m_tool->on_motion (this, i, ev);
	return true;
}

} // namespace gmojo
