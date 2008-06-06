
#include "track_view.hpp"

#include "track_canvas_factory.hpp"

#include "track_view_item_factory.hpp"
#include "project.hpp"

#include "log.hpp"

namespace ui {

TrackView::TrackView(Project* p)
	: m_project(p)
	, m_canvas(TrackCanvasFactory::create (p))
{
	m_project->signal_track_added().connect ( sigc::mem_fun
		       	(this, &TrackView::on_track_added));

	m_project->signal_track_removed().connect ( sigc::mem_fun
		       	(this, &TrackView::on_track_removed));

	m_scrolled_window.add (*m_canvas);

	pack2 (m_scrolled_window);
}

TrackView::~TrackView ()
{

}

void
TrackView::on_track_added (Track* track)
{
	LOG;

	TrackViewItemSPtr tvi(TrackViewItemFactory::create (track));

	if (tvi)
	{
		m_track_view_items.push_back (tvi);
	}
}

void
TrackView::on_track_removed (Track* track)
{
	LOG;
}

} // namespace ui
