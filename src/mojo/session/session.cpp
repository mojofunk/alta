
#include <boost/bind.hpp>

#include "session.hpp"
#include "session_bus.hpp"
#include "session_data.hpp"

namespace mojo {

Session::Session ()
{
	data = new internal::SessionData;

	data->dispatcher.run();
}

Session::~Session ()
{
	data->dispatcher.quit();
	delete data;
}

void
Session::add_bus (SessionBus* bus)
{
	data->dispatcher.call_sync (boost::bind (&Session::add_bus_internal, this, bus));
}

void
Session::remove_bus (SessionBus* bus)
{
	data->dispatcher.call_sync (boost::bind (&Session::remove_bus_internal, this, bus));
}

void
Session::new_project ()
{
	data->dispatcher.call_async (boost::bind (&Session::new_project_internal, this));
}

void
Session::open_project (const std::string& project_file)
{
	data->dispatcher.call_async (boost::bind (&Session::open_project_internal, this, project_file));
}

void
Session::save_project_as (Project*, const std::string& filename)
{

}

void
Session::save_project (Project*)
{

}

void
Session::close_project (Project* p)
{
	data->dispatcher.call_async (boost::bind (&Session::close_project_internal, this, p));
}

void
Session::add_track (const TrackOptions& options)
{
	data->dispatcher.call_async (boost::bind (&Session::add_track_internal, this, options));
}

} // namespace mojo
