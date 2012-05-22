
#include "application_event_handler.hpp"

#include "log.hpp"

namespace ui {

ApplicationEventHandler::ApplicationEventHandler ()
{

}

ApplicationEventHandler::~ApplicationEventHandler ()
{

}

void
ApplicationEventHandler::on_project_added (mojo::Project* p)
{
	LOG;
	m_dispatcher.call_async (sigc::bind (m_signal_project_added, p));
}

void
ApplicationEventHandler::on_project_removed (mojo::Project* p)
{
	LOG;
	m_dispatcher.call_sync (sigc::bind (m_signal_project_removed, p));
}

void
ApplicationEventHandler::on_project_saved (mojo::Project* p)
{

}

void
ApplicationEventHandler::on_track_added (mojo::Project* p, mojo::Track* t)
{
	m_dispatcher.call_async (sigc::bind (m_signal_track_added, p, t));
}

void
ApplicationEventHandler::on_track_removed (mojo::Project* p, mojo::Track* t)
{
	m_dispatcher.call_sync (sigc::bind (m_signal_track_removed, p, t));
}

void
ApplicationEventHandler::on_project_property_changed (mojo::Project*, mojo::Property*)
{

}

void
ApplicationEventHandler::on_active_project_changed (mojo::Project* p)
{
	m_dispatcher.call_async (sigc::bind (m_signal_active_project_changed, p));
}

void
ApplicationEventHandler::on_track_property_changed (mojo::Project*, mojo::Track*, mojo::Property*)
{

}

void
ApplicationEventHandler::on_transport_speed_changed (mojo::Project* p, float speed)
{
	m_dispatcher.call_async (sigc::bind (m_signal_transport_speed_changed, p, speed));
}

void
ApplicationEventHandler::on_transport_position_changed (mojo::Project* p, mojo::count_t pos)
{
	m_dispatcher.call_async (sigc::bind (m_signal_transport_position_changed, p, pos));
}

void
ApplicationEventHandler::on_transport_record_changed (mojo::Project* p, bool record)
{
	m_dispatcher.call_async (sigc::bind (m_signal_transport_record_changed, p, record));
}

} // namespace ui
