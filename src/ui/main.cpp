
#include <gtk/gtk.h>

#include <ui/application.hpp>
#include <ui/signal_handler.hpp>

#include <afl/audio_file_factory.hpp>

#include <mojo/mojo.hpp>

using namespace gmojo;

#include <iostream>

using namespace std;

int
main(int argc, char* argv[])
{
	SignalHandler	signal_handler;

	gtk_init(&argc, &argv);


	afl::factory_func_t factory_func = 0;

	GModule* module = NULL;
	GError* error = NULL;

	module = g_module_open ( "./build/release/afl/libafl_sndfile.so", G_MODULE_BIND_LAZY );

	if ( !module )
	{
		cerr << "module == NULL:" << g_module_error() << endl;
		return EXIT_FAILURE;
	} 

	if ( !g_module_symbol (module, "factory", (gpointer*)&factory_func))
	{
		cerr << "g_module" << endl;
		return EXIT_FAILURE;
	}

	if (factory_func == NULL)
	{
		cerr << "factory_func == NULL" << endl;
		return EXIT_FAILURE;
	}

	afl::AudioFileFactory* audio_file_factory = static_cast<afl::AudioFileFactory*>(factory_func());

	cerr << audio_file_factory->name() << endl;

#if 0
	{
		boost::shared_ptr<Application> gmojo_app = Application::create(argc, argv);

		gmojo_app->run();
	}
#endif

    return EXIT_SUCCESS;
}
