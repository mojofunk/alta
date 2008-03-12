
#ifndef GMOJO_OBJECT_SELECTION_TOOL_INCLUDED
#define GMOJO_OBJECT_SELECTION_TOOL_INCLUDED

#include <ui/tools/tool.hpp>

namespace gmojo {

class ObjectSelectionTool : public Tool
{
public:

	ObjectSelectionTool ();

public: // Tool interface
	
	const std::string get_name() const;

	virtual void on_button_press (TrackCanvas*, CanvasItem*, GdkEventButton*);
	
	virtual void on_button_release (TrackCanvas*, CanvasItem*, GdkEventButton*);

};

}

#endif
