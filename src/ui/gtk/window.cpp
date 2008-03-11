
#include <ui/gtk/window.hpp>

namespace gtk {

gboolean
Window::window_delete_event_handler (GtkWidget* widget,
		GdkEvent* event, gpointer data )
{
	Window* window = static_cast<Window*>(data);

	return window->delete_event_handler (widget, event);
}

} // namespace gtk
