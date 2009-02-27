
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

	static void quit ();

	static void open_project ();

	static void new_project ();

	static void save_project (mojo::Project*);

	static void close_project (mojo::Project*);

	static void show_about_window ();

	static Bus& get_session_bus ();

private:

        static void on_new_project (mojo::Project*);

        static void on_close_project (mojo::Project*);

	static AppData* s_data;

};

}

#endif
