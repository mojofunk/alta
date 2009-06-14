#include "session.hpp"

#include <mojo/mojo-internal.hpp>

#include "session_bus.hpp"
#include "session_data.hpp"
#include "null_deleter.hpp"
#include "utils.hpp"

#include "log.hpp"

namespace mojo {

void
Session::add_bus_internal (SessionBus* bus)
{
	LOG;
	data->busses.insert (bus);
}

void
Session::remove_bus_internal (SessionBus* bus)
{
	LOG;
	data->busses.erase (bus);
}

void
Session::new_project_internal ()
{
	ProjectSP pi(new Project);
	LOG;

	data->projects.insert (pi);

	for (std::set<SessionBus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (pi.get());
	}
}

void
Session::open_project_internal (const std::string& project_file)
{
	ProjectSP pi(new Project);

	LOG;
	// load project state from project file

	data->projects.insert (pi);

	for (std::set<SessionBus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (pi.get());
	}

}

void
Session::close_project_internal (Project* p)
{
	LOG;
	ProjectSP sp(p, internal::null_deleter());

	//std::set<ProjectSP>::iterator i = data->projects.find (sp);
	std::set<ProjectSP>::iterator i;

	for (i = data->projects.begin ();
			i != data->projects.end(); ++i)
	{
		if (sp == *i) break;
	}

	if (i == data->projects.end())
	{
		// send an error
		return;
	}

	for (std::set<SessionBus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_removed (sp.get());
	}

	data->projects.erase (i);
}

void
Session::add_track_internal (const TrackOptions& options)
{
	//std::cerr << "Options type: " << track_type_to_string (options.type) << std::endl;
	//std::cerr << "Options count: " << options.count << std::endl;
}

} // namespace mojo
