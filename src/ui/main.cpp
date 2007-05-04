
#include <gleam.hpp>
#include <cformat.hpp>
#include <mojo.hpp>

#include <gtk/gtk.h>

#include "application.hpp"
#include "signal_handler.hpp"

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

#if 0
	gtk_init(&argc, &argv);

	{
		boost::shared_ptr<Application> gmojo_app = Application::create(argc, argv);

		gmojo_app->run();
	}
#endif

	mojo::ProjectFormat format;

	const string state_file = "./testout.xml";

	{
		mojo::Project l_project;

		l_project.set_name("baba");

		{

			std::list<boost::shared_ptr<mojo::AudioTrack> > delete_list;

			for (int count = 1; count <= 10; ++count)
			{
				mojo::AudioTrack* new_track = new mojo::AudioTrack;

				boost::shared_ptr<mojo::AudioTrack> track_ptr(new_track);

				delete_list.push_back(track_ptr);

				std::cout << "Track Address: " << new_track << std::endl;

				std::string track_name = "New Track";

				track_name += cformat::value_to_string(count);

				std::cout << track_name << std::endl;

				new_track->set_name(track_name);

				l_project.add_audio_track(new_track);
			}

			mojo::Project::AudioTrackList::const_iterator iter = l_project.track_list().begin();
			mojo::Project::AudioTrackList::const_iterator end = l_project.track_list().end();

			for(; iter != end; ++iter)
			{
				std::cout << "Track Address: " << (*iter) << std::endl;
				std::cout << "Track name: " << (*iter)->get_name() << std::endl;

			}

			format.save_project(l_project, state_file);

		}

	}

	{
		boost::shared_ptr<mojo::Project> l_project_ptr(format.load_project(state_file));

		std::cout << "Project Name: " << l_project_ptr->get_name() << std::endl;

		mojo::Project::AudioTrackList::const_iterator iter = l_project_ptr->track_list().begin();
		mojo::Project::AudioTrackList::const_iterator end = l_project_ptr->track_list().end();

		for(; iter != end; ++iter)
		{
			std::cout << "Track Address: " << (*iter) << std::endl;
			std::cout << "Track name: " << (*iter)->get_name() << std::endl;

		}
		
	}

#ifdef GMOJO_DEBUG
	gleam::thread_map().unregister_thread(gui_thread_name);
#endif

    return EXIT_SUCCESS;
}
