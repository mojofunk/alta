
#include <gtkmm.h>

#include "app.hpp"
#include "project_setup_dialog.hpp"
#include "preferences_dialog.hpp"
#include "import_dialog.hpp"

#include "log.hpp"

namespace ui {

App* App::s_app = 0;

void
App::init (int argc, char *argv[])
{
	if (s_app) throw;

	s_app = new App(argc, argv);
}

void
App::cleanup ()
{
	delete s_app;
}

App::App (int argc, char *argv[])
{
	m_session_event_handler.signal_project_added().connect (&App::on_project_added);
	m_session_event_handler.signal_project_removed().connect (&App::on_project_removed);

	// must add after connecting signals to ensure
	// thread safety of signals?
	m_session.add_event_handler(&m_session_event_handler);
}

App::~App ()
{
	m_session.remove_event_handler(&m_session_event_handler);
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
        s_app->m_session.new_project ();
}

void
App::on_project_added (mojo::Project* p)
{
        boost::shared_ptr<ProjectObjects> po(new ProjectObjects(p));

	s_app->project_objs.insert (po);

	LOG;
}

void
App::on_project_removed (mojo::Project* p)
{
	LOG;
	for(project_objects_set_t::iterator i = s_app->project_objs.begin();
			i != s_app->project_objs.end(); ++i)
	{
		if (p == (*i)->get_project())
		{
			s_app->project_objs.erase(i);
		}

		if (s_app->project_objs.empty ()) {
			// this is a problem??
			quit();
		}
	}
}

void
App::close_project (mojo::Project* p)
{
	// TODO ask about saving
	LOG;
        s_app->m_session.close_project (p);
}

void
App::save_project (mojo::Project* p)
{
        s_app->m_session.save_project (p);
}

void
App::add_track (mojo::Project* p)
{
	mojo::TrackOptions opt;
	// bring up add audio track dialog
	s_app->m_session.add_track (p, opt);
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
	return s_app->m_session_event_handler;
}

mojo::Session&
App::get_session ()
{
	return s_app->m_session;
}

} // namespace ui
