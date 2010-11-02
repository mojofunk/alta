
#include "session_event_handler.hpp"

#include "log.hpp"

namespace ui {

SessionEventHandler::SessionEventHandler ()
{

}

SessionEventHandler::~SessionEventHandler ()
{

}

void
SessionEventHandler::on_project_added (mojo::Project* p)
{
	LOG;
	m_dispatcher.call_async (sigc::bind (m_signal_project_added, p));
}

void
SessionEventHandler::on_project_removed (mojo::Project* p)
{
	LOG;
	m_dispatcher.call_sync (sigc::bind (m_signal_project_removed, p));
}

void
SessionEventHandler::on_project_saved (mojo::Project* p)
{

}

void
SessionEventHandler::on_track_added (mojo::Project* p, mojo::Track* t)
{
	m_dispatcher.call_async (sigc::bind (m_signal_track_added, p, t));
}

void
SessionEventHandler::on_track_removed (mojo::Project* p, mojo::Track* t)
{
	m_dispatcher.call_sync (sigc::bind (m_signal_track_removed, p, t));
}

void
SessionEventHandler::on_project_property_changed (mojo::Project*, mojo::Property*)
{

}

void
SessionEventHandler::on_track_property_changed (mojo::Project*, mojo::Track*, mojo::Property*)
{

}

void
SessionEventHandler::on_transport_speed_changed (mojo::Project* p, float speed)
{
	m_dispatcher.call_async (sigc::bind (m_signal_transport_speed_changed, p, speed));
}

void
SessionEventHandler::on_transport_position_changed (mojo::Project* p, mojo::count_t pos)
{
	m_dispatcher.call_async (sigc::bind (m_signal_transport_position_changed, p, pos));
}

void
SessionEventHandler::on_transport_record_changed (mojo::Project* p, bool record)
{
	m_dispatcher.call_async (sigc::bind (m_signal_transport_record_changed, p, record));
}

} // namespace ui
