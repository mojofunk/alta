
#include <gtk/gtk.h>

#include <mojo/mojo.hpp>

#include <ui/app.hpp>
#include <ui/utils/signal_handler.hpp>

using namespace gmojo;

#include <iostream>

using namespace std;

int
main(int argc, char* argv[])
{
	SignalHandler	signal_handler;

	gtk_init(&argc, &argv);

	// need to initialize mojo::App and show progress, scanning plugins etc.
	boost::shared_ptr<mojo::Application> mojo_app = mojo::Application::init(argc, argv);

	boost::shared_ptr<App> gmojo_app = App::init(argc, argv);

	gmojo_app->run();

	return EXIT_SUCCESS;
}
