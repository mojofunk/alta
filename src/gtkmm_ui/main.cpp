
#include <gtkmm.h>

#include <mojo/core/debug.hpp>

#include "app.hpp"

using namespace ui;

int
main(int argc, char* argv[])
{
	Glib::thread_init ();

	mojo::debug::set_enabled(mojo::debug::get_domain_index("APPLICATION"), true);

	Gtk::Main app (argc, argv);

	App::init (argc, argv);

	App::run ();

	App::cleanup ();

	return 0;
}
