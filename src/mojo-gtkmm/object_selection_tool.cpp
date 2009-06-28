
#include "object_selection_tool.hpp"

#include "log.hpp"

namespace ui {

ObjectSelectionTool::ObjectSelectionTool ()
{

}

const std::string
ObjectSelectionTool::get_name () const
{
	return "Object Selection";
}

bool
ObjectSelectionTool::on_button_press (Goocanvas::Canvas* canvas,
		Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* event)
{
	LOG;
	return true;
}

bool
ObjectSelectionTool::on_button_release (Goocanvas::Canvas* canvas,
		Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* event)
{
	LOG;
	return true;
}

bool
ObjectSelectionTool::on_motion (Goocanvas::Canvas* canvas,
		Glib::RefPtr<Goocanvas::Item> item, GdkEventMotion* event)
{
	LOG;
	return true;
}

} // namespace ui
