
#include <gleam.hpp>
#include <cformat.hpp>
#include <mojo.hpp>

#include <gtkmm/main.h>

#include "signal_handler.hpp"

#include "debug.hpp"

using namespace gmojo;

int
main(int argc, char* argv[])
{
	Glib::thread_init();

#ifdef GMOJO_DEBUG
	gleam::thread_map().register_thread(gmojo::gui_thread_name);
#endif

	SignalHandler	signal_handler;

	Gtk::Main kit(argc, argv);

#ifdef GMOJO_DEBUG_EXTRA

	LOG_GMOJO_DEBUG << mojo::get_unique_filename ("/home/timbyr", "audio", ".wav");
	LOG_GMOJO_DEBUG << mojo::get_unique_filename ("/home/timbyr", "audio", ".wav");

#endif

#ifdef GMOJO_DEBUG
	gleam::thread_map().unregister_thread(gmojo::gui_thread_name);
#endif

    return EXIT_SUCCESS;
}
