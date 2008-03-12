#include <goocanvas.h>

#include <ui/track_canvas.hpp>

#include <ui/canvas_group.hpp>

#include <iostream>

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

bool
TrackCanvas::on_button_press_event (CanvasItem*, GdkEventButton*)
{
	std::cerr << "button press" << std::endl;
	return true;
}

bool
TrackCanvas::on_button_release_event (CanvasItem*, GdkEventButton*)
{
	std::cerr << "button release" << std::endl;
	return true;
}

bool
TrackCanvas::on_motion_notify_event (CanvasItem*, GdkEventMotion*)
{
	std::cerr << "motion" << std::endl;
	return true;
}

} // namespace gmojo
