
#include <boost/bind.hpp>

#include <ui/track_view.hpp>

#include <ui/project.hpp>
#include <ui/track.hpp>

#include <ui/audio_track.hpp>
#include <ui/audio_track_view_item.hpp>

#include <ui/track_control.hpp>
#include <ui/track_canvas.hpp>

namespace gmojo {

TrackView::TrackView(Project* project)
	:
		m_project(project)
		, m_scrolled_window(gtk_scrolled_window_new (NULL, NULL))
		, m_hpaned(gtk_hpaned_new ())
		, m_track_control_vbox(gtk_vbox_new(FALSE, 0))
		, m_canvas(new TrackCanvas)
{
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (m_scrolled_window),
			GTK_SHADOW_IN);

	// add canvas to scrolled window
	gtk_container_add (GTK_CONTAINER (m_scrolled_window), m_canvas->get_widget ());

	// pack horizontal paned
	gtk_paned_pack1(GTK_PANED (m_hpaned), m_track_control_vbox, TRUE, TRUE);
	gtk_paned_pack2(GTK_PANED (m_hpaned), m_scrolled_window, TRUE, TRUE);

	gtk_widget_show_all (m_hpaned);

	m_project->track_added_signal().connect ( boost::bind (&TrackView::on_track_added, this, _1));
}

TrackView::~TrackView()
{

}

void
TrackView::on_track_added (Track* track)
{
	TrackViewItem* tvi = create_track_view_item (track);

	m_track_views.push_back (tvi);

	GtkWidget* track_controls = tvi->get_track_control ()->get_widget ();

	gtk_box_pack_end (GTK_BOX (m_track_control_vbox),
			track_controls,
			FALSE,
			TRUE,
			0);

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
