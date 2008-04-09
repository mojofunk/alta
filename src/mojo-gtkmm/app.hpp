
#ifndef UI_APP_INCLUDED
#define UI_APP_INCLUDED

namespace ui {

class Project;
class AppData;

class App
{
public:

	static void init ();

	static void run ();

	static void quit ();

	static void open_project ();

	static void new_project ();

	static void close_project (Project*);

	static void show_about_window ();

private:

	static AppData* s_data;

};

}

#endif
