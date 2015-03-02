#include "track_view.hpp"

#include <mojo/api/project.hpp>

#include "app.hpp"
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
	p->connect_track_added(
		boost::bind (&TrackView::on_track_added_handler, this, _1));

	p->connect_track_removed(
		boost::bind (&TrackView::on_track_removed_handler, this, _1));

	pack1 (*m_track_list);
	pack2 (*m_canvas);
}

TrackView::~TrackView ()
{

}

void
TrackView::on_track_added_handler (mojo::Track* track)
{
	App::get_dispatcher().call_async (sigc::bind (sigc::mem_fun (this, &TrackView::on_track_added), track));
}

void
TrackView::on_track_removed_handler (mojo::Track* track)
{
	App::get_dispatcher().call_sync (sigc::bind (sigc::mem_fun (this, &TrackView::on_track_removed), track));
}

void
TrackView::on_track_added (mojo::Track* track)
{
	TrackViewItemSPtr tvi(TrackViewItemFactory::create (track));

	if (!tvi) throw; // do something smart

	m_track_view_items.push_back (tvi);

	m_track_list->add(tvi->get_track_list_item ());
	m_canvas->add(tvi->get_track_canvas_item ());
}

void
TrackView::on_track_removed (mojo::Track* track)
{

	LOG;
}

} // namespace ui
