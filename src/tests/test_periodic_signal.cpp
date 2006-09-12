
#include <gleam.hpp>

#include <gtkmm/main.h>

#include "debug.hpp"

#ifdef GMOJO_DEBUG

#include <libgleam/log_domain.hpp>

#endif

gleam::atomic_counter counter;

void
on_timeout ()
{

	++counter;
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG
		<< "Counter value" << counter.get();
#endif

	if(counter.get() == 10)
	{

#ifdef GMOJO_DEBUG_EXTRA
		LOG_GMOJO_DEBUG
			<< "Quiting Gtk MainLoop";
#endif

		Gtk::Main::quit();
	}

}

int
main(int argc, char* argv[])
{
	Glib::thread_init();

#ifdef GMOJO_DEBUG
	gleam::thread_map().register_thread(gmojo::gui_thread_name);
#endif

	gleam::PeriodicSignal  one_second_timeout(1000);

	one_second_timeout.signal().connect(sigc::ptr_fun(&on_timeout));

	Gtk::Main kit(argc, argv);

	kit.run();

#ifdef GMOJO_DEBUG
	gleam::thread_map().unregister_thread(gmojo::gui_thread_name);
#endif

    return EXIT_SUCCESS;
}
