
#ifndef UI_TRACK_CANVAS_FACTORY
#define UI_TRACK_CANVAS_FACTORY

#include "track_canvas.hpp"

namespace ui {

class Project;

class TrackCanvasFactory
{
public:

	static TrackCanvas* create (Project* proj);
};

} // namespace ui

#endif
