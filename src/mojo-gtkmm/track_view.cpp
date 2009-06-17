
#include "track_view.hpp"

#include "app.hpp"
#include "bus.hpp"
#include "track_canvas_factory.hpp"
#include "track_view_item_factory.hpp"

#include "log.hpp"

namespace ui {

TrackView::TrackView(mojo::Project* p)
	: m_project(p)
	, m_canvas(TrackCanvasFactory::create (p))
{
	App::get_session_bus().signal_track_added().connect (
			sigc::mem_fun (this, &TrackView::on_track_added));

	App::get_session_bus().signal_track_removed().connect (
			sigc::mem_fun (this, &TrackView::on_track_removed));

	pack2 (*m_canvas);
}

TrackView::~TrackView ()
{

}

void
TrackView::on_track_added (mojo::Project* p, mojo::Track* track)
{
	if (p != m_project) return;

	TrackViewItemSPtr tvi(TrackViewItemFactory::create (track));

	if (tvi)
	{
		LOG;
		m_track_view_items.push_back (tvi);
	}
}

void
TrackView::on_track_removed (mojo::Project* p, mojo::Track* track)
{
	if (p != m_project) return;

	LOG;
}

} // namespace ui
