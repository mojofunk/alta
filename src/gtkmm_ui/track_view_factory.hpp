
#ifndef UI_TRACK_VIEW_FACTORY
#define UI_TRACK_VIEW_FACTORY

#include "track_view.hpp"

namespace ui {

class TrackViewFactory {
public:
	static TrackView* create(mojo::Project* proj);
};

} // namespace ui

#endif
