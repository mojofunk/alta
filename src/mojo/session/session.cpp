
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
	boost::function<void()> func;

	func = boost::bind (&Session::new_project_async, this);

	data->queue.push (func);

	boost::function<void()> func_async;

	func_async = data->queue.pop ();

	func_async ();

}

void
Session::open_project (const std::string& project_file)
{
	project_t p;

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (p);
	}
}

void
Session::save_project_as (project_t, const std::string& filename)
{

}

void
Session::save_project (project_t)
{

}

void
Session::close_project (project_t)
{
	project_t p;

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_removed (p);
	}
}

} // namespace mojo
