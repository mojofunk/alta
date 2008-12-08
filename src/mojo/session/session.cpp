
#include <boost/bind.hpp>

#include "session.hpp"
#include "bus.hpp"
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
Session::add_bus (Bus* bus)
{
	data->dispatcher.queue (boost::bind (&Session::add_bus_internal, this, bus));
	data->dispatcher.iteration(true);
}

void
Session::remove_bus (Bus* bus)
{
	data->dispatcher.queue (boost::bind (&Session::remove_bus_internal, this, bus));
	data->dispatcher.iteration(true);
}

void
Session::new_project ()
{
	data->dispatcher.queue (boost::bind (&Session::new_project_internal, this));
}

void
Session::open_project (const std::string& project_file)
{
	data->dispatcher.queue (boost::bind (&Session::open_project_internal, this, project_file));
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
	data->dispatcher.queue (boost::bind (&Session::close_project_internal, this, p));
}

void
Session::add_track (const TrackOptions& options)
{
	data->dispatcher.queue (boost::bind (&Session::add_track_internal, this, options));
}

} // namespace mojo
