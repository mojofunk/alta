
#include <gtkmm.h>

#include "app.hpp"
#include "project_setup_dialog.hpp"
#include "preferences_dialog.hpp"
#include "import_dialog.hpp"

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


	s_data->m_session_event_handler.signal_project_added().connect (&App::on_project_added);
	s_data->m_session_event_handler.signal_project_removed().connect (&App::on_project_removed);

	// must add after connecting signals to ensure
	// thread safety of signals?
	s_data->m_session.add_event_handler(&s_data->m_session_event_handler);
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
        boost::shared_ptr<ProjectObjects> po(new ProjectObjects(p));

	s_data->project_objs.insert (po);

	LOG;
}

void
App::on_project_removed (mojo::Project* p)
{
	LOG;
	for(AppData::project_objects_set_t::iterator i = s_data->project_objs.begin();
			i != s_data->project_objs.end(); ++i)
	{
		if (p == (*i)->get_project())
		{
			s_data->project_objs.erase(i);
		}

		if (s_data->project_objs.empty ()) {
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

void
App::add_track (mojo::Project* p)
{
	mojo::TrackOptions opt;
	// bring up add audio track dialog
	s_data->m_session.add_track (p, opt);
}

void
App::open_project_setup_dialog (mojo::Project* proj)
{
	LOG;
	ProjectSetupDialog dialog(proj);

	dialog.run();
}

void
App::open_preferences_dialog ()
{
	PreferencesDialog dialog;
	LOG;

	dialog.run();
}

void
App::open_import_dialog ()
{
	ImportDialog dialog;
	LOG;

	dialog.run();
}

SessionEventHandler&
App::get_session_event_handler ()
{
	return s_data->m_session_event_handler;
}

mojo::Session&
App::get_session ()
{
	return s_data->m_session;
}

} // namespace ui
