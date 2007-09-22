
#include <gtk/gtk.h>

#include <mojo/mojo.hpp>

#include <ark/module.hpp>

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

#if 0
	{

		ark::Module dummy_module ("./build/debug/ark/libdummy_archive.so");

		boost::shared_ptr<ark::ArchiveWriter> writer(dummy_module.new_writer());

		boost::shared_ptr<mojo::Project> project(new mojo::Project);

		writer->add_property(ark::Property("project", boost::any(project)));

		mojo::TypeNameRegistry reg;

		writer->write ("text.archive", reg);

	}
#endif

    return EXIT_SUCCESS;
}
