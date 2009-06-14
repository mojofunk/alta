
#include <boost/bind.hpp>

#include "session.hpp"
#include "session_bus.hpp"
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
	delete data;
}

void
Session::add_bus (SessionBus* bus)
{
	LOG;
	data->worker.call_sync (boost::bind (&Session::add_bus_internal, this, bus));
}

void
Session::remove_bus (SessionBus* bus)
{
	LOG;
	data->worker.call_sync (boost::bind (&Session::remove_bus_internal, this, bus));
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
Session::close_project (Project* p)
{
	LOG;
	data->worker.call_async (boost::bind (&Session::close_project_internal, this, p));
}

void
Session::add_track (const TrackOptions& options)
{
	LOG;
	data->worker.call_async (boost::bind (&Session::add_track_internal, this, options));
}

} // namespace mojo
