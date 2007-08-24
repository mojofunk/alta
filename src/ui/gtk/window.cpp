
#include <ui/gtk/window.hpp>

namespace gtk {

	gboolean Window::window_delete_event_handler (GtkWidget* widget,
			GdkEvent* event, gpointer data )
	{
		Window* window = static_cast<Window*>(data);

		return window->delete_event_handler (widget, event);
	}

	Window::connection_t Window::on_delete_event (const delete_signal_t::slot_type& handler)
	{ return m_signal_delete_event.connect(handler); }

} // namespace gtk
