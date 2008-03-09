
#ifndef GMOJO_TRACK_CANVAS_INCLUDED
#define GMOJO_TRACK_CANVAS_INCLUDED

#include <ui/canvas/canvas.hpp>

namespace gmojo {

/**
 * The TrackCanvas should not depend on the TrackCanvasTool
 * Interface. One option would be to transform canvas api specific
 * events into generic events that are emitted by the TrackCanvas
 * so that classes outside of the TrackCanvas don't depend 
 * on the canvas implementation.
 *
 * Does the TrackCanvas need to handle any events itself? 
 *
 */
class TrackCanvas : public goo::Canvas
{
public:

protected:

	// list of TrackCanvasItems


};


}

#endif
