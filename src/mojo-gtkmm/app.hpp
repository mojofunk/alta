
#ifndef UI_APP
#define UI_APP

#include <mojo/mojo.hpp>

namespace ui {

class AppData;
class Bus;

class App
{
public:

	static void init ();

	static void run ();

	static void fini ();

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

	static Bus& get_session_bus ();

private:

        static void on_project_added (mojo::Project*);

        static void on_project_removed (mojo::Project*);

	static AppData* s_data;

};

}

#endif
