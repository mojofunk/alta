
#include "track_view.hpp"

#include "project.hpp"

namespace ui {

TrackView::TrackView(Project* p)
	: m_project(p)
{
	m_project->signal_track_added().connect ( sigc::mem_fun
		       	(this, &TrackView::on_track_added_handler));

	m_project->signal_track_removed().connect ( sigc::mem_fun
		       	(this, &TrackView::on_track_removed_handler));
}

TrackView::~TrackView ()
{

}

void
TrackView::on_track_added_handler (Track* track)
{
	on_track_added (track);
}

void
TrackView::on_track_removed_handler (Track* track)
{
	on_track_removed (track);
}

} // namespace ui
