#ifndef UI_DEFAULT_TRANSPORT_TOOLBAR
#define UI_DEFAULT_TRANSPORT_TOOLBAR

#include <gtkmm/buttonbox.h>
#include <gtkmm/togglebutton.h>

#include "transport_toolbar.hpp"

namespace ui {

class DefaultTransportToolbar : public TransportToolbar
{
public:

	DefaultTransportToolbar (Project*);

private:

	void update_transport_buttons ();

	void on_loop_button_toggled ();
	void on_play_button_toggled ();

private:

	Gtk::HButtonBox m_button_box;

	Gtk::ToggleButton m_loop_button;
	Gtk::ToggleButton m_play_button;

};

} // namespace ui

#endif
