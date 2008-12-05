#include "session.hpp"

#include <mojo/mojo-internal.hpp>

#include "bus.hpp"
#include "session_data.hpp"
#include "null_deleter.hpp"
#include "utils.hpp"

#include <iostream>

namespace mojo {

void
Session::new_project_internal ()
{
	ProjectSP pi(new Project);
	std::cerr << "Project: " << pi.get() << std::endl;

	data->projects.insert (pi);

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (pi.get());
	}
}

void
Session::open_project_internal (const std::string& project_file)
{
	ProjectSP pi(new Project);

	std::cerr << "Project: " << pi.get() << std::endl;
	// load project state from project file

	data->projects.insert (pi);

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (pi.get());
	}

}

void
Session::close_project_internal (Project* p)
{
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
		std::cerr << "project not found" << std::endl;
		std::cerr << "Project: " << p << std::endl;
		// send and error
		return;
	}

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_removed (sp.get());
	}

	std::cerr << "Project Removed: " << sp.get() << std::endl;

	data->projects.erase (i);
}

void
Session::add_track_internal (const TrackOptions& options)
{
	std::cerr << "Options type: " << track_type_to_string (options.type) << std::endl;
	std::cerr << "Options count: " << options.count << std::endl;
}

} // namespace mojo
