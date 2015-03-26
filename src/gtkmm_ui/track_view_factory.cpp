#include "track_view_factory.hpp"

#include "track_view.hpp"

namespace ui {

TrackView* TrackViewFactory::create(mojo::Project* proj)
{
	return new TrackView(proj);
}

} // namespace ui
