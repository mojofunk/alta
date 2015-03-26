
#include "app.hpp"

#include "transport_toolbar.hpp"

namespace ui {

TransportToolbar::TransportToolbar(mojo::Project* p)
    : m_project(p)
    , m_loop_button("Loop")
    , m_play_button("Play")
{
	m_button_box.pack_start(m_loop_button, false, false);
	m_button_box.pack_start(m_play_button, false, false);

	pack_start(m_button_box, false, false);

	/*
	m_loop_button.signal_toggled().connect (sigc::mem_fun (this,
	 &TransportToolbar::on_loop_button_toggled));
	m_play_button.signal_toggled().connect (sigc::mem_fun (this,
	 &TransportToolbar::on_play_button_toggled));

	m_project->transport_changed_signal().connect (sigc::mem_fun (this,
	   &TransportToolbar::update_transport_buttons));
	*/

	update_transport_buttons();
}

void TransportToolbar::update_transport_buttons()
{
	//	m_loop_button.set_active (m_project->get_looping ());
	//	m_play_button.set_active (m_project->get_playing ());
}

void TransportToolbar::on_loop_button_toggled()
{
	//	m_project->set_looping (m_loop_button.get_active ());
}

void TransportToolbar::on_play_button_toggled()
{
	//	m_project->set_playing (m_play_button.get_active ());
}

} // namespace ui
