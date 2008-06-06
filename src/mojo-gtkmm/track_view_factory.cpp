
#include "track_view_factory.hpp"

#include "default_track_view.hpp"

namespace ui {

TrackView*
TrackViewFactory::create (Project* proj)
{
	return new DefaultTrackView (proj);
}

} // namespace ui
