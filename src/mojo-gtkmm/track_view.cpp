
#include "track_view.hpp"

#include "track_view_data.hpp"
#include "track_view_item_factory.hpp"
#include "project.hpp"

#include "log.hpp"

namespace ui {

TrackView::TrackView(Project* p)
	: m_data (new TrackViewData)
{
	m_data->project = p;

	m_data->project->signal_track_added().connect ( sigc::mem_fun
		       	(this, &TrackView::on_track_added));

	m_data->project->signal_track_removed().connect ( sigc::mem_fun
		       	(this, &TrackView::on_track_removed));
}

TrackView::~TrackView ()
{
	delete m_data;
}

void
TrackView::on_track_added (Track* track)
{
	LOG;

	TrackViewItemSPtr tvi(TrackViewItemFactory::create (track));

	if (tvi)
	{
		m_data->track_view_items.push_back (tvi);
	}
}

void
TrackView::on_track_removed (Track* track)
{
	LOG;
}

} // namespace ui
