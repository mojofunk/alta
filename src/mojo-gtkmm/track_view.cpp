
#include "track_view.hpp"

#include "app.hpp"
#include "session_event_handler.hpp"
#include "track_canvas.hpp"
#include "track_view_item_factory.hpp"
#include "track_list.hpp"
#include "track_list_item.hpp"

#include "log.hpp"

namespace ui {

TrackView::TrackView(mojo::Project* p)
	: m_project(p)
	, m_track_list(new TrackList)
	, m_canvas(new TrackCanvas())
{
	App::get_session_event_handler().signal_track_added().connect (
			sigc::mem_fun (this, &TrackView::on_track_added));

	App::get_session_event_handler().signal_track_removed().connect (
			sigc::mem_fun (this, &TrackView::on_track_removed));

	pack1 (*m_track_list);
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

	if (!tvi) throw; // do something smart

	m_track_view_items.push_back (tvi);

	m_track_list->add(tvi->get_track_list_item ());
	m_canvas->add(tvi->get_track_canvas_item ());
}

void
TrackView::on_track_removed (mojo::Project* p, mojo::Track* track)
{
	if (p != m_project) return;

	LOG;
}

} // namespace ui
