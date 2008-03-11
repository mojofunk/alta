
#ifndef GMOJO_GTK_WINDOW_INCLUDED
#define GMOJO_GTK_WINDOW_INCLUDED

#include <gtk/gtk.h>

#include <boost/signal.hpp>

namespace gtk
{

class Window
{
public:

	typedef boost::signal<bool ()> delete_signal_t;

public:

	Window ()
		: m_window (gtk_window_new (GTK_WINDOW_TOPLEVEL))
	{
		g_signal_connect (G_OBJECT (m_window), "delete-event",
				G_CALLBACK (Window::window_delete_event_handler), this);
	}

	virtual ~Window () { gtk_widget_destroy (GTK_WIDGET (m_window)); }

public:

	delete_signal_t& delete_event_signal ()
	{ return m_signal_delete_event; }

private:

	static gboolean window_delete_event_handler (GtkWidget*, GdkEvent*,
				gpointer edit_window);

	bool delete_event_handler (GtkWidget* widget, GdkEvent* event)
	{
		g_assert (widget == m_window);
		return m_signal_delete_event ();
	}

protected:
	
	GtkWidget* m_window;

private:
	
	// signals
	delete_signal_t m_signal_delete_event;
};

} // namespace gtk

#endif
