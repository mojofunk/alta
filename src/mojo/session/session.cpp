
#include "session.hpp"
#include "bus.hpp"

namespace mojo {

Session::Session () { }

Session::~Session () { }

void
Session::add_bus (Bus* bus)
{
	busses.insert (bus);

}

void
Session::remove_bus (Bus* bus)
{
	busses.erase (bus);
}

void
Session::new_project ()
{
	Project *p = NULL;

	for (std::set<Bus*>::iterator i = busses.begin();
			i != busses.end(); ++i)
	{
		(*i)->on_project_added (p);
	}

}

void
Session::open_project (const std::string& project_file)
{
	Project *p = NULL;

	for (std::set<Bus*>::iterator i = busses.begin();
			i != busses.end(); ++i)
	{
		(*i)->on_project_added (p);
	}
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
Session::close_project (Project*)
{
	Project *p = NULL;

	for (std::set<Bus*>::iterator i = busses.begin();
			i != busses.end(); ++i)
	{
		(*i)->on_project_removed (p);
	}
}

} // namespace mojo
