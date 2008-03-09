
#include <ui/track_view.hpp>

#include <ui/project.hpp>
#include <ui/track.hpp>

#include <ui/audio_track.hpp>
#include <ui/audio_track_view_item.hpp>

#include <ui/canvas/canvas.hpp>

namespace gmojo {

TrackView::TrackView(Project* project)
	:
		m_project(project)
		, m_scrolled_window(gtk_scrolled_window_new (NULL, NULL))
		, m_label(gtk_label_new("Track Control List"))
		, m_hpaned(gtk_hpaned_new ())
		, m_canvas(new goo::Canvas())
{
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (m_scrolled_window),
			GTK_SHADOW_IN);

	// add canvas to scrolled window
	gtk_container_add (GTK_CONTAINER (m_scrolled_window), m_canvas->get_widget ());

	// pack horizontal paned
	gtk_paned_pack1(GTK_PANED (m_hpaned), m_label, TRUE, TRUE);
	gtk_paned_pack2(GTK_PANED (m_hpaned), m_scrolled_window, TRUE, TRUE);

	gtk_widget_show_all (m_hpaned);

}

TrackView::~TrackView()
{

}

void
TrackView::on_track_added (Track* track)
{
	TrackViewItem* tvi = create_track_view_item (track);

	m_track_views.push_back (tvi);

	//m_track_control_list.insert (tvi->get_track_control ());

	//m_track_canvas.insert (tvi->get_track_canvas_item ());
}

void
TrackView::on_track_removed (Track* track)
{


}

TrackViewItem*
TrackView::create_track_view_item (Track* track)
{
	AudioTrack* audio_track = dynamic_cast<AudioTrack*>(track);

	if (audio_track)
	{
		return new AudioTrackViewItem (audio_track);
	}

	return 0;
}

} // namespace gmojo
