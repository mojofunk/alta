
#include <boost/bind.hpp>

#include "mojo/project/audio_track.hpp"

#include "mojo/core/debug.hpp"

#include "application.hpp"
#include "application_event_handler.hpp"
#include "application_data.hpp"

namespace {

	mojo::Application* s_application = 0;

}

namespace mojo {

void
Application::init (int argc, char *argv[])
{
	if(s_application) throw;

	// try/catch?
	s_application = new Application();
}

void
Application::cleanup ()
{
	delete s_application;
}

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
	delete s_application->data;
}

void
Application::add_event_handler (ApplicationEventHandler* event_handler)
{
	LOG;
	s_application->data->worker.call_sync (boost::bind (&Application::add_event_handler_internal, s_application, event_handler));
}

void
Application::remove_event_handler (ApplicationEventHandler* event_handler)
{
	LOG;
	s_application->data->worker.call_sync (boost::bind (&Application::remove_event_handler_internal, s_application, event_handler));
}

void
Application::new_project ()
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::new_project_internal, s_application));
}

void
Application::open_project (const std::string& project_file)
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::open_project_internal, s_application, project_file));
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
	if (s_application->data->active_project == p) return;
	s_application->data->worker.call_async (boost::bind (&Application::set_active_project_internal, s_application, p));
}

Project*
Application::get_active_project()
{
	return s_application->data->active_project;
}

void
Application::close_project (Project* p)
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::close_project_internal, s_application, p));
}

void
Application::add_track (Project* p, const TrackOptions& options)
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::add_track_internal, s_application, p, options));
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
	s_application->data->worker.call_async (boost::bind (&Application::transport_set_speed_internal, s_application, speed));
}

float
Application::transport_get_speed ()
{
	return s_application->data->speed;
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
	s_application->data->worker.call_async (boost::bind (&Application::transport_set_position_internal, s_application, pos));
}

count_t
Application::transport_get_position ()
{
	return s_application->data->position;
}

void
Application::transport_set_record (bool record)
{
	s_application->data->worker.call_async (boost::bind (&Application::transport_set_record_internal, s_application, record));
}

bool
Application::transport_get_record ()
{
	return s_application->data->record;
}

} // namespace mojo
