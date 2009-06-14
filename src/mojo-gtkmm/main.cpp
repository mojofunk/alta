
#include <gtkmm.h>

#include "app.hpp"

using namespace ui;

int
main(int argc, char* argv[])
{
	Glib::thread_init ();

	Gtk::Main app (argc, argv);

	App::init ();

	App::run ();

	return 0;
}
