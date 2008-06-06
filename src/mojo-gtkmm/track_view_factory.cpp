
#include "track_view_factory.hpp"

#include "track_view.hpp"

namespace ui {

TrackView*
TrackViewFactory::create (Project* proj)
{
	return new TrackView (proj);
}

} // namespace ui
