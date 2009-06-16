
#include <gtkmm.h>

#include "app.hpp"

#include "app_data.hpp"

#include "log.hpp"

namespace ui {

AppData* App::s_data = 0;

void
App::init ()
{
	if (!s_data)
	{
		s_data = new AppData;
	}


	s_data->m_bus.signal_project_added().connect (&App::on_project_added);
	s_data->m_bus.signal_project_removed().connect (&App::on_project_removed);

	// must add after connecting signals to ensure
	// thread safety of signals?
	s_data->m_session.add_bus(&s_data->m_bus);
}

void
App::fini ()
{
	if (s_data)
	{
		delete s_data;
	}

}

void
App::run ()
{
	new_project ();

	Gtk::Main::run ();
}

void
App::quit ()
{
	LOG;
	Gtk::Main::quit ();
}

void
App::open_project ()
{
	LOG;
}

void
App::new_project ()
{
	LOG;
        s_data->m_session.new_project ();
}

void
App::on_project_added (mojo::Project* p)
{
        boost::shared_ptr<ProjectWindows> project_windows(new ProjectWindows(p));

	s_data->projects.insert (project_windows);

	LOG;
}

void
App::on_project_removed (mojo::Project* p)
{
	LOG;
	for(AppData::project_windows_set_t::iterator i = s_data->projects.begin();
			i != s_data->projects.end(); ++i)
	{
		if (p == (*i)->get_project())
		{
			s_data->projects.erase(i); 
		}

		if (s_data->projects.empty ()) {
			// this is a problem
			quit();
		}
	}
}

void
App::close_project (mojo::Project* p)
{
	// TODO ask about saving
	LOG;
        s_data->m_session.close_project (p);
}

void
App::save_project (mojo::Project* p)
{
        s_data->m_session.save_project (p);
}

Bus&
App::get_session_bus ()
{
	return s_data->m_bus;
}

} // namespace ui
