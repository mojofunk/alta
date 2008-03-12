
#include <ui/tools/object_selection_tool.hpp>

namespace gmojo {

ObjectSelectionTool::ObjectSelectionTool ()
{

}

const std::string
ObjectSelectionTool::get_name () const
{
	return "Object Selection";
}

void
ObjectSelectionTool::on_button_press (TrackCanvas* canvas,
		CanvasItem* item, GdkEventButton* event)
{

}

void
ObjectSelectionTool::on_button_release (TrackCanvas* canvas,
		CanvasItem* item, GdkEventButton* event)
{

}
	
} // namespace gmojo
