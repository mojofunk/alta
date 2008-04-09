
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
	Project* p = new Project;
	ProjectWindows* windows = new ProjectWindows(p);

	s_data->projects.insert (std::make_pair (p, windows));

	cout << "App::new_project called" << endl;

}

void
App::close_project (Project* p)
{
	cerr << "close project called" << endl;
	// ask about saving etc.

	for(AppData::project_map_t::iterator i = s_data->projects.begin();
			i != s_data->projects.end(); ++i)
	{
		if (p == i->first.get())
		{
			cerr << "erasing project" << endl;
			s_data->projects.erase(i); 
		}

		if (s_data->projects.empty ())
			quit();
	}
}

} // namespace ui
