
#include "mojo/core/debug.hpp"
#include "mojo/core/null_deleter.hpp"


#include "application.hpp"
#include "application_data.hpp"
#include "audio_track.hpp"
#include "project.hpp"
#include "utils.hpp"

namespace mojo {

void
Application::new_project_internal ()
{
	ProjectSP pi(new Project);
	LOG;

	data->projects.insert (pi);

	// sync signal
	data->m_project_added(pi.get());
}

void
Application::open_project_internal (const std::string& project_file)
{
	ProjectSP pi(new Project);

	LOG;
	// load project state from project file

	data->projects.insert (pi);

	// signal async
}

void
Application::close_project_internal (Project* p)
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

	// signal sync
	data->m_project_removed(p);

	data->projects.erase (i);
}

void
Application::set_active_project_internal (Project* p)
{
	// data->engine->reset();

	if (data->active_project == p)
	{
		return;
	}

	data->active_project = p;

	// signal sync?
}

void
Application::add_track_internal (Project* p, const TrackOptions& options)
{
	//std::cerr << "Options type: " << track_type_to_string (options.type) << std::endl;
	//std::cerr << "Options count: " << options.count << std::endl;

	LOG;

	TrackSP t(new AudioTrack);

	p->add_track (t);

	// signal async
}

} // namespace mojo
