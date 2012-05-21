
#include <boost/bind.hpp>

#include "session.hpp"
#include "session_event_handler.hpp"
#include "session_data.hpp"

#include "log.hpp"

namespace mojo {

Session::Session ()
{
	LOG;
	data = new internal::SessionData;

	const sigc::slot<void> main_func = sigc::mem_fun
		(
			data->worker,
			&SessionWorker::run
		);

	data->worker_thread = Glib::Thread::create(main_func, true);
}

Session::~Session ()
{
	LOG;
	data->worker.quit();
	data->worker_thread->join ();
	delete data;
}

void
Session::add_event_handler (SessionEventHandler* event_handler)
{
	LOG;
	data->worker.call_sync (boost::bind (&Session::add_event_handler_internal, this, event_handler));
}

void
Session::remove_event_handler (SessionEventHandler* event_handler)
{
	LOG;
	data->worker.call_sync (boost::bind (&Session::remove_event_handler_internal, this, event_handler));
}

void
Session::new_project ()
{
	LOG;
	data->worker.call_async (boost::bind (&Session::new_project_internal, this));
}

void
Session::open_project (const std::string& project_file)
{
	LOG;
	data->worker.call_async (boost::bind (&Session::open_project_internal, this, project_file));
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
Session::set_active_project(Project* p)
{
	if (data->active_project == p) return;
	data->worker.call_async (boost::bind (&Session::set_active_project_internal, this, p));
}

Project*
Session::get_active_project() const
{
	return data->active_project;
}

void
Session::close_project (Project* p)
{
	LOG;
	data->worker.call_async (boost::bind (&Session::close_project_internal, this, p));
}

void
Session::add_track (Project* p, const TrackOptions& options)
{
	LOG;
	data->worker.call_async (boost::bind (&Session::add_track_internal, this, p, options));
}

bool
Session::is_audio_track (Track* t)
{
	return dynamic_cast<AudioTrack*>(t);
}

void
Session::transport_set_speed (float speed)
{
	LOG;
	data->worker.call_async (boost::bind (&Session::transport_set_speed_internal, this, speed));
}

float
Session::transport_get_speed ()
{
	return data->speed;
}

void
Session::transport_stop ()
{
	transport_set_speed (0);
}

void
Session::transport_play ()
{
	transport_set_speed (1.0);
}

void
Session::transport_set_position (count_t pos)
{
	data->worker.call_async (boost::bind (&Session::transport_set_position_internal, this, pos));
}

count_t
Session::transport_get_position ()
{
	return data->position;
}

void
Session::transport_set_record (bool record)
{
	data->worker.call_async (boost::bind (&Session::transport_set_record_internal, this, record));
}

bool
Session::transport_get_record ()
{
	return data->record;
}

} // namespace mojo
