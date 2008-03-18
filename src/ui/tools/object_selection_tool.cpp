
#include <ui/tools/object_selection_tool.hpp>

#include <iostream>

namespace gmojo {

ObjectSelectionTool::ObjectSelectionTool ()
{

}

const std::string
ObjectSelectionTool::get_name () const
{
	return "Object Selection";
}

bool
ObjectSelectionTool::on_button_press (TrackCanvas* canvas,
		CanvasItem* item, GdkEventButton* event)
{
	std::cerr << "Object Selection button press" << std::endl;
	return true;
}

bool
ObjectSelectionTool::on_button_release (TrackCanvas* canvas,
		CanvasItem* item, GdkEventButton* event)
{
	std::cerr << "Object Selection button release" << std::endl;
	return true;
}

bool
ObjectSelectionTool::on_motion (TrackCanvas* canvas,
		CanvasItem* item, GdkEventMotion* event)
{
	std::cerr << "Object Selection motion" << std::endl;
	return true;
}
	
} // namespace gmojo
