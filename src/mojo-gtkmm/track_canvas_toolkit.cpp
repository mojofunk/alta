
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

}
