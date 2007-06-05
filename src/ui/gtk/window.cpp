
#include <ui/gtk/window.hpp>

namespace gtk {

	Window::Window ()
		:
			m_window (gtk_window_new (GTK_WINDOW_TOPLEVEL))
	{
		g_signal_connect (G_OBJECT (m_window), "delete-event",
				G_CALLBACK (Window::window_delete_event_handler), this);

	}

	Window::~Window ()
	{
		gtk_widget_destroy (GTK_WIDGET (m_window));
	}

	gboolean Window::window_delete_event_handler (GtkWidget* widget,
			GdkEvent* event, gpointer data )
	{
		Window* window = static_cast<Window*>(data);

		return window->delete_event_handler (widget, event);
	}

	bool Window::delete_event_handler (GtkWidget* widget, GdkEvent* event)
	{
		g_assert (widget == m_window);

		return m_signal_delete_event ();
	}

} // namespace gtk
