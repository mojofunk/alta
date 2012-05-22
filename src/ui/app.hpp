
#ifndef UI_APP
#define UI_APP

#include <set>

#include <boost/shared_ptr.hpp>

#include <mojo/mojo.hpp>

#include "project_objects.hpp"
#include "application_event_handler.hpp"

namespace ui {

class App
{
private: // typedefs

	typedef std::set< boost::shared_ptr<ProjectObjects> > project_objects_set_t;

public:

	static void init (int argc, char *argv[]);

	static void run ();

	static void cleanup ();

	static void quit ();

	static void open_project ();

	static void new_project ();

	static void save_project (mojo::Project*);

	static void close_project (mojo::Project*);

	static void add_track (mojo::Project*);

	static void remove_track (mojo::Project*, mojo::Track*);

	static void show_about_window ();

	static void open_project_setup_dialog (mojo::Project*);

	static void open_preferences_dialog ();

	static void open_import_dialog ();

	static ApplicationEventHandler& get_application_event_handler ();

	static mojo::Application& get_application ();

private:

	App (int argc, char *argv[]);

	~App ();

        static void on_project_added (mojo::Project*);

        static void on_project_removed (mojo::Project*);


private: // member data

	static App* s_app;

	project_objects_set_t project_objs;

        mojo::Application m_application;
	ApplicationEventHandler m_application_event_handler;

};

}

#endif
