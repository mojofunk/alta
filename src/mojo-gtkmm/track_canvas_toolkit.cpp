
#include "track_canvas_toolkit.hpp"

#include "object_selection_tool.hpp"

#include "log.hpp"

namespace ui {

TrackCanvasToolkit::TrackCanvasToolkit ()
{
	LOG;
	ToolSP tool(new ObjectSelectionTool);

	add_tool (tool);
	set_current_tool (tool);
}

bool
TrackCanvasToolkit::on_button_press (Goocanvas::Canvas* canvas,
		Glib::RefPtr<Goocanvas::Item> item,
		GdkEventButton* ev)
{
	LOG;
	m_current_tool->on_button_press (canvas, item, ev);
	return true;
}

bool
TrackCanvasToolkit::on_button_release (Goocanvas::Canvas* canvas,
		Glib::RefPtr<Goocanvas::Item> item,
		GdkEventButton* ev)
{
	LOG;
	m_current_tool->on_button_release (canvas, item, ev);
	return true;
}

bool
TrackCanvasToolkit::on_motion (Goocanvas::Canvas* canvas,
		Glib::RefPtr<Goocanvas::Item> item,
		GdkEventMotion* ev)
{
	LOG;
	m_current_tool->on_motion (canvas, item, ev);
	return true;
}

}
