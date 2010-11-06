#include "session.hpp"

#include <mojo/mojo-internal.hpp>

#include "session_event_handler.hpp"
#include "session_data.hpp"
#include "null_deleter.hpp"
#include "utils.hpp"

#include "log.hpp"

namespace mojo {

void
Session::add_event_handler_internal (SessionEventHandler* bus)
{
	LOG;
	data->event_handlers.insert (bus);
}

void
Session::remove_event_handler_internal (SessionEventHandler* bus)
{
	LOG;
	data->event_handlers.erase (bus);
}

void
Session::new_project_internal ()
{
	ProjectSP pi(new Project);
	LOG;

	data->projects.insert (pi);

	for (std::set<SessionEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
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

	for (std::set<SessionEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
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

	for (std::set<SessionEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_project_removed (sp.get());
	}

	data->projects.erase (i);
}

void
Session::set_active_project_internal (Project* p)
{
	// data->engine->reset();

	if (data->active_project == p)
	{
		return;
	}

	data->active_project = p;

	for (std::set<SessionEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_active_project_changed (p);
	}

}

void
Session::add_track_internal (Project* p, const TrackOptions& options)
{
	//std::cerr << "Options type: " << track_type_to_string (options.type) << std::endl;
	//std::cerr << "Options count: " << options.count << std::endl;

	LOG;

	TrackSP t(new AudioTrack);

	p->add_track (t);

	for (std::set<SessionEventHandler*>::iterator i = data->event_handlers.begin();
			i != data->event_handlers.end(); ++i)
	{
		(*i)->on_track_added (p, t.get());
	}
}

void
Session::transport_set_speed_internal (float speed)
{
	data->speed = speed;
}

void
Session::transport_set_position_internal (count_t pos)
{
	data->position = pos;
}

void
Session::transport_set_record_internal (bool record)
{
	data->record = record;
}

} // namespace mojo
