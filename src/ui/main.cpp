
#include <gtk/gtk.h>

#include <ui/application.hpp>
#include <ui/signal_handler.hpp>

using namespace gmojo;

int
main(int argc, char* argv[])
{
	SignalHandler	signal_handler;

	gtk_init(&argc, &argv);

	{
		boost::shared_ptr<Application> gmojo_app = Application::create(argc, argv);

		gmojo_app->run();
	}

    return EXIT_SUCCESS;
}
