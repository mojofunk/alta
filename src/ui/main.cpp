
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

	// need to initialize mojo::App and show progress, scanning plugins etc.
	mojo::AppSPtr mojo_app = mojo::App::init(argc, argv);

	AppSPtr gmojo_app = App::init(argc, argv);

	gmojo_app->run();

	return EXIT_SUCCESS;
}
