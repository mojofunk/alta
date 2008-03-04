
#include <ui/app.hpp>
#include <ui/utils/signal_handler.hpp>

using namespace gmojo;

int
main(int argc, char* argv[])
{
	SignalHandler	signal_handler;

	AppSPtr gmojo_app = App::init(argc, argv);

	gmojo_app->run();

	return EXIT_SUCCESS;
}
