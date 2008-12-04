
#include <boost/bind.hpp>

#include "session.hpp"
#include "bus.hpp"
#include "session_data.hpp"

namespace mojo {

Session::Session ()
{
	data = new internal::SessionData;
}

Session::~Session ()
{
	delete data;
}

void
Session::add_bus (Bus* bus)
{
	data->busses.insert (bus);

}

void
Session::remove_bus (Bus* bus)
{
	data->busses.erase (bus);
}

void
Session::new_project ()
{
	data->queue.push (boost::bind (&Session::new_project_internal, this));
	data->queue.pop ()();
}

void
Session::open_project (const std::string& project_file)
{
	data->queue.push (boost::bind (&Session::open_project_internal, this, project_file));
	data->queue.pop ()();
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
	data->queue.push (boost::bind (&Session::close_project_internal, this, p));
	data->queue.pop ()();
}

} // namespace mojo
