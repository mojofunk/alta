
#include "default_track_view.hpp"
#include "project.hpp"

namespace ui {

DefaultTrackView::DefaultTrackView (Project* p)
	: TrackView(p)
{
	pack_start (m_hpaned);
}

} // namespace ui
