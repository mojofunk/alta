
#include "track_canvas_factory.hpp"

namespace ui {

TrackCanvas*
TrackCanvasFactory::create (Project* proj)
{
	return new TrackCanvas ();
}

} // namespace ui
