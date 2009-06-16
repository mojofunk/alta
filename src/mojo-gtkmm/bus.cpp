
#include "bus.hpp"

#include "log.hpp"

namespace ui {

Bus::Bus ()
{

}

Bus::~Bus ()
{

}

void
Bus::on_project_added (mojo::Project* p)
{
	LOG;
	m_dispatcher.call_async (sigc::bind (m_signal_project_added, p));
}

void
Bus::on_project_removed (mojo::Project* p)
{
	LOG;
	m_dispatcher.call_sync (sigc::bind (m_signal_project_removed, p));
}

void
Bus::on_project_saved (mojo::Project* p)
{

}

void
Bus::on_track_added (mojo::Project* p, mojo::Track* t)
{

}

void
Bus::on_track_removed (mojo::Project* p, mojo::Track* t)
{

}

} // namespace ui
