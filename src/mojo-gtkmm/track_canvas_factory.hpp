
#ifndef UI_TRACK_CANVAS_FACTORY
#define UI_TRACK_CANVAS_FACTORY

#include "track_canvas.hpp"

#include <mojo/mojo.hpp>

namespace ui {

class TrackCanvasFactory
{
public:

	static TrackCanvas* create (mojo::Project* proj);
};

} // namespace ui

#endif
