
#include <mojo/mojo-internal.hpp>

#include "bus.hpp"
#include "session.hpp"
#include "session_data.hpp"

namespace mojo {

void
Session::new_project_internal ()
{
	ProjectSP pi(new Project);
	data->projects.insert (pi);

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (pi);
	}
}

void
Session::open_project_internal (const std::string& project_file)
{
	ProjectSP pi(new Project);

	// load project state from project file

	data->projects.insert (pi);

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (pi);
	}

}

void
Session::close_project_internal (project_t p)
{
	ProjectSP pi = p.ptr.lock();

	if (pi)
	{
		for (std::set<Bus*>::iterator i = data->busses.begin();
				i != data->busses.end(); ++i)
		{
			(*i)->on_project_removed (pi);
		}
		data->projects.erase (pi);
	}
	else
	{
		// ummm

	}
}


} // namespace mojo
