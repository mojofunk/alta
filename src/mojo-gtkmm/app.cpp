
#include <gtkmm.h>

#include "app.hpp"

#include "app_data.hpp"

#include <iostream>

using namespace std;

namespace ui {

AppData* App::s_data = 0;

void
App::init ()
{
	if (!s_data)
	{
		s_data = new AppData;
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
	cout << "App::quit called" << endl;
	Gtk::Main::quit ();
}

void
App::open_project ()
{
	cout << "App::open_project called" << endl;
}

void
App::new_project ()
{
        s_data->m_session.new_project ();
}

void
App::on_new_project (mojo::Project* p)
{
        boost::shared_ptr<ProjectWindows> project_windows(new ProjectWindows(p));

	s_data->projects.insert (project_windows);

	cout << "App::new_project called" << endl;

}

void
App::close_project (mojo::Project* p)
{
        s_data->m_session.close_project (p);
}

void
App::save_project (mojo::Project* p)
{
        s_data->m_session.save_project (p);
}

void
App::on_close_project (mojo::Project* p)
{
	cerr << "close project called" << endl;
	// ask about saving etc.

	for(AppData::project_windows_set_t::iterator i = s_data->projects.begin();
			i != s_data->projects.end(); ++i)
	{
		if (p == (*i)->get_project())
		{
			cerr << "erasing project" << endl;
			s_data->projects.erase(i); 
		}

		if (s_data->projects.empty ())
			quit();
	}
}

Bus&
App::get_session_bus ()
{
	return s_data->m_bus;
}

} // namespace ui
