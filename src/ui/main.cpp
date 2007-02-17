
#include <gleam.hpp>
#include <cformat.hpp>
#include <mojo.hpp>

#include <gtkmm/main.h>

#include "application.hpp"
#include "signal_handler.hpp"

#include "debug.hpp"

using namespace gmojo;

int
main(int argc, char* argv[])
{
	Glib::thread_init();

#ifdef GMOJO_DEBUG
	gleam::thread_map().register_thread(gui_thread_name);
#endif

	SignalHandler	signal_handler;

	Gtk::Main kit(argc, argv);

	boost::shared_ptr<Application> gmojo_app = Application::create(argc, argv);

	gmojo_app->run();

#ifdef GMOJO_DEBUG
	gleam::thread_map().unregister_thread(gui_thread_name);
#endif

    return EXIT_SUCCESS;
}
