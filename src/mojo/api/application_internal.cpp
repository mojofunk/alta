
#include "mojo/core/debug.hpp"
#include "mojo/core/null_deleter.hpp"

#include "mojo/project/project.hpp"
#include "mojo/project/audio_track.hpp"

#include "application.hpp"
#include "application_event_handler.hpp"
#include "application_data.hpp"
#include "utils.hpp"

namespace mojo {

void
Application::add_event_handler_internal (ApplicationEventHandler* bus)
{
	LOG;
	data->event_handlers.insert (bus);
}

void
Application::remove_event_handler_internal (ApplicationEventHandler* bus)
{
	LOG;
	data->event_handlers.erase (bus);
}

void
Application::new_project_internal ()
{
	ProjectSP pi(new Project);
	LOG;

	data->projects.insert (pi);

	for (std::set<ApplicationEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_project_added (pi.get());
	}
}

void
Application::open_project_internal (const std::string& project_file)
{
	ProjectSP pi(new Project);

	LOG;
	// load project state from project file

	data->projects.insert (pi);

	for (std::set<ApplicationEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_project_added (pi.get());
	}

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

	for (std::set<ApplicationEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_project_removed (sp.get());
	}

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

	for (std::set<ApplicationEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_active_project_changed (p);
	}

}

void
Application::add_track_internal (Project* p, const TrackOptions& options)
{
	//std::cerr << "Options type: " << track_type_to_string (options.type) << std::endl;
	//std::cerr << "Options count: " << options.count << std::endl;

	LOG;

	TrackSP t(new AudioTrack);

	p->add_track (t);

	for (std::set<ApplicationEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_track_added (p, t.get());
	}
}

void
Application::transport_set_speed_internal (float speed)
{
	data->speed = speed;
}

void
Application::transport_set_position_internal (count_t pos)
{
	data->position = pos;
}

void
Application::transport_set_record_internal (bool record)
{
	data->record = record;
}

} // namespace mojo
