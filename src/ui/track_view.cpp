
#include <ui/track_view.hpp>

#include <ui/canvas/canvas.hpp>

namespace gmojo {

TrackView::TrackView(mojo::ProjectSPtr project)
	:
		m_project(project),
		m_scrolled_window(gtk_scrolled_window_new (NULL, NULL)),
		m_label(gtk_label_new("Track Control List")),
		m_hpaned(gtk_hpaned_new ()),
		m_canvas(new goo::Canvas())
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

} // namespace gmojo
