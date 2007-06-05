
#include <cformat.hpp>
#include <mojo.hpp>

#include <gtk/gtk.h>

#include <ui/application.hpp>
#include <ui/signal_handler.hpp>

#include <ui/debug/debug.hpp>

#ifdef GMOJO_DEBUG
#include <gleam.hpp>
#endif

using namespace gmojo;

int
main(int argc, char* argv[])
{
#ifdef GMOJO_DEBUG
	g_thread_init(NULL);
	
	gleam::thread_map().register_thread(gui_thread_name);

	SignalHandler	signal_handler;
#endif

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
