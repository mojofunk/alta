
#include <gleam.hpp>
#include <cformat.hpp>
#include <mojo.hpp>

#include <gtk/gtk.h>

#include <ui/application.hpp>
#include <ui/signal_handler.hpp>

#include "debug.hpp"

#include <iostream>

using std::cout;
using std::cerr;

using namespace gmojo;

int
main(int argc, char* argv[])
{
	g_thread_init(NULL);

#ifdef GMOJO_DEBUG
	gleam::thread_map().register_thread(gui_thread_name);
#endif

	SignalHandler	signal_handler;

	gtk_init(&argc, &argv);

	{
		boost::shared_ptr<Application> gmojo_app = Application::create(argc, argv);

		gmojo_app->run();
	}

#ifdef GMOJO_DEBUG
	gleam::thread_map().unregister_thread(gui_thread_name);
#endif

    return EXIT_SUCCESS;
}
