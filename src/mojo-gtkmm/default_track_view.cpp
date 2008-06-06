
#include "default_track_view.hpp"
#include "project.hpp"

#include "log.hpp"

namespace ui {

DefaultTrackView::DefaultTrackView (Project* p)
	: TrackView(p)
{
	pack_start (m_hpaned);
}

void
DefaultTrackView::on_track_added (Track* track)
{
	LOG;

}

void
DefaultTrackView::on_track_removed (Track* track)
{

}

} // namespace ui
