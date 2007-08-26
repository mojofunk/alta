
#include <gtk/gtk.h>

#include <mojo/mojo.hpp>

#include <afl/audio_file_factory.hpp>

#include <ui/application.hpp>
#include <ui/signal_handler.hpp>

using namespace gmojo;

#include <iostream>

using namespace std;

int
main(int argc, char* argv[])
{
	SignalHandler	signal_handler;

	gtk_init(&argc, &argv);

	// need to initialize mojo::Application and show progress, scanning plugins etc.
	boost::shared_ptr<mojo::Application> mojo_app = mojo::Application::create(argc, argv);

	boost::shared_ptr<Application> gmojo_app = Application::create(argc, argv);

	gmojo_app->run();

    return EXIT_SUCCESS;
}
