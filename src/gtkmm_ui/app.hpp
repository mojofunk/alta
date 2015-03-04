
#ifndef UI_APP
#define UI_APP

#include <set>

#include <boost/shared_ptr.hpp>

#include <mojo-application.hpp>

#include "dispatcher.hpp"
#include "project_objects.hpp"

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

private:

	App (int argc, char *argv[]);

	~App ();

	static void on_project_added_handler (mojo::Project*);

	static void on_project_removed_handler (mojo::Project*);

	static void on_project_added (mojo::Project*);

	static void on_project_removed (mojo::Project*);

public:

	static Dispatcher& get_dispatcher ();

private: // member data

	static App* s_app;

	project_objects_set_t project_objs;

	Dispatcher m_dispatcher;

};

}

#endif
