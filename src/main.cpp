
#include <gleam.hpp>
#include <cformat.hpp>

#include <gtkmm/main.h>

#include "debug.hpp"

#ifdef GMOJO_DEBUG

#include <libgleam/log_domain.hpp>

#endif

int
main(int argc, char* argv[])
{
	Glib::thread_init();

#ifdef GMOJO_DEBUG
	gleam::thread_map().register_thread(gmojo::gui_thread_name);
#endif

	Gtk::Main kit(argc, argv);


#ifdef GMOJO_DEBUG
	gleam::thread_map().unregister_thread(gmojo::gui_thread_name);
#endif

    return EXIT_SUCCESS;
}
