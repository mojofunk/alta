namespace ui {

TrackCanvasToolkit::TrackCanvasToolkit()
{
	LOG;
	ToolSP tool(new ObjectSelectionTool);

	add_tool(tool);
	set_current_tool(tool);
}
}
