
#include <boost/bind.hpp>

#include "mojo/core/debug.hpp"

#include "application.hpp"
#include "application_event_handler.hpp"
#include "application_data.hpp"


namespace mojo {

Application::Application ()
{
	LOG;
	data = new internal::ApplicationData;

	const sigc::slot<void> main_func = sigc::mem_fun
		(
			data->worker,
			&ApplicationWorker::run
		);

	data->worker_thread = Glib::Thread::create(main_func, true);
}

Application::~Application ()
{
	LOG;
	data->worker.quit();
	data->worker_thread->join ();
	delete data;
}

void
Application::add_event_handler (ApplicationEventHandler* event_handler)
{
	LOG;
	data->worker.call_sync (boost::bind (&Application::add_event_handler_internal, this, event_handler));
}

void
Application::remove_event_handler (ApplicationEventHandler* event_handler)
{
	LOG;
	data->worker.call_sync (boost::bind (&Application::remove_event_handler_internal, this, event_handler));
}

void
Application::new_project ()
{
	LOG;
	data->worker.call_async (boost::bind (&Application::new_project_internal, this));
}

void
Application::open_project (const std::string& project_file)
{
	LOG;
	data->worker.call_async (boost::bind (&Application::open_project_internal, this, project_file));
}

void
Application::save_project_as (Project*, const std::string& filename)
{

}

void
Application::save_project (Project*)
{

}

void
Application::set_active_project(Project* p)
{
	if (data->active_project == p) return;
	data->worker.call_async (boost::bind (&Application::set_active_project_internal, this, p));
}

Project*
Application::get_active_project() const
{
	return data->active_project;
}

void
Application::close_project (Project* p)
{
	LOG;
	data->worker.call_async (boost::bind (&Application::close_project_internal, this, p));
}

void
Application::add_track (Project* p, const TrackOptions& options)
{
	LOG;
	data->worker.call_async (boost::bind (&Application::add_track_internal, this, p, options));
}

bool
Application::is_audio_track (Track* t)
{
	return dynamic_cast<AudioTrack*>(t);
}

void
Application::transport_set_speed (float speed)
{
	LOG;
	data->worker.call_async (boost::bind (&Application::transport_set_speed_internal, this, speed));
}

float
Application::transport_get_speed ()
{
	return data->speed;
}

void
Application::transport_stop ()
{
	transport_set_speed (0);
}

void
Application::transport_play ()
{
	transport_set_speed (1.0);
}

void
Application::transport_set_position (count_t pos)
{
	data->worker.call_async (boost::bind (&Application::transport_set_position_internal, this, pos));
}

count_t
Application::transport_get_position ()
{
	return data->position;
}

void
Application::transport_set_record (bool record)
{
	data->worker.call_async (boost::bind (&Application::transport_set_record_internal, this, record));
}

bool
Application::transport_get_record ()
{
	return data->record;
}

} // namespace mojo
