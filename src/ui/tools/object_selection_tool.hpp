
#ifndef GMOJO_OBJECT_SELECTION_TOOL_INCLUDED
#define GMOJO_OBJECT_SELECTION_TOOL_INCLUDED

namespace gmojo {

class ObjectSelectionTool : public Tool
{
public:

	ObjectSelectionTool();

public:
	
	// CanvasTool interface
	const string get_name() const;

}

}

#endif
