
#include "default_transport_toolbar.hpp"
#include "project.hpp"

namespace ui {

DefaultTransportToolbar::DefaultTransportToolbar (Project* p)
	: TransportToolbar(p)
	, m_loop_button ("Loop")
	, m_play_button ("Play")
{
	m_button_box.pack_start (m_loop_button, false, false);
	m_button_box.pack_start (m_play_button, false, false);

	pack_start (m_button_box, false, false);

	m_loop_button.signal_toggled().connect (sigc::mem_fun (this,
		       	&DefaultTransportToolbar::on_loop_button_toggled));
	m_play_button.signal_toggled().connect (sigc::mem_fun (this,
		       	&DefaultTransportToolbar::on_play_button_toggled));

	m_project->transport_changed_signal().connect (sigc::mem_fun (this,
				&DefaultTransportToolbar::update_transport_buttons));

	update_transport_buttons ();
}

void
DefaultTransportToolbar::update_transport_buttons ()
{
	m_loop_button.set_active (m_project->get_looping ());
	m_play_button.set_active (m_project->get_playing ());
}

void
DefaultTransportToolbar::on_loop_button_toggled ()
{
	m_project->set_looping (m_loop_button.get_active ());
}

void
DefaultTransportToolbar::on_play_button_toggled ()
{
	m_project->set_playing (m_play_button.get_active ());
}

} // namespace ui
