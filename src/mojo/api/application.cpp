
#include <boost/bind.hpp>

#include "mojo/core/debug.hpp"
#include "mojo/core/module_utils.hpp"

#include "mojo/typesystem/type_system.hpp"
#include "mojo/typesystem/template_type_factory.hpp"

#include "mojo/core/type_names.hpp"

#include "mojo/api/object_collection.hpp"
#include "mojo/api/audio_track.hpp"
#include "mojo/api/midi_track.hpp"
#include "mojo/api/audio_sequence.hpp"
#include "mojo/api/audio_event.hpp"

#include "mojo/interfaces/audio_file_module.hpp"
#include "mojo/interfaces/audio_driver_module.hpp"
#include "mojo/interfaces/audio_effect_module.hpp"
#include "mojo/interfaces/archive.hpp"
#include "mojo/interfaces/archive_module.hpp"

#include "mojo/fs/filesystem_paths.hpp"

#include "application.hpp"
#include "application_event_handler.hpp"
#include "application_data.hpp"
#include "audio_track.hpp"

namespace {

	mojo::Application* s_application = 0;

}

namespace mojo {

void
Application::init (int argc, char *argv[])
{
	if(s_application) throw;

	Glib::thread_init ();

	// try/catch?
	s_application = new Application();
}

void
Application::cleanup ()
{
	delete s_application;
}

Application::Application ()
{
	LOG;
	data = new internal::ApplicationData;

	TypeSystem::init ();

	register_types ();

	data->m_modules = discover_modules (module_search_path ());

	const sigc::slot<void> main_func = sigc::mem_fun
		(
			data->worker,
			&FunctorDispatcher::run
		);

	data->worker_thread = Glib::Thread::create(main_func, true);
}

Application::~Application ()
{
	LOG;
	data->worker.quit();
	data->worker_thread->join ();

	TypeSystem::cleanup ();

	delete s_application->data;
}

void
Application::add_event_handler (ApplicationEventHandler* event_handler)
{
	LOG;
	s_application->data->worker.call_sync (boost::bind (&Application::add_event_handler_internal, s_application, event_handler));
}

void
Application::remove_event_handler (ApplicationEventHandler* event_handler)
{
	LOG;
	s_application->data->worker.call_sync (boost::bind (&Application::remove_event_handler_internal, s_application, event_handler));
}

void
Application::new_project ()
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::new_project_internal, s_application));
}

void
Application::open_project (const std::string& project_file)
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::open_project_internal, s_application, project_file));
}

void
Application::save_project_as (Project*, const std::string& filename)
{

}

void
Application::save_project (Project*)
{

}

void
Application::set_active_project(Project* p)
{
	if (s_application->data->active_project == p) return;
	s_application->data->worker.call_async (boost::bind (&Application::set_active_project_internal, s_application, p));
}

Project*
Application::get_active_project()
{
	return s_application->data->active_project;
}

void
Application::close_project (Project* p)
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::close_project_internal, s_application, p));
}

void
Application::add_track (Project* p, const TrackOptions& options)
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::add_track_internal, s_application, p, options));
}

bool
Application::is_audio_track (Track* t)
{
	return dynamic_cast<AudioTrack*>(t);
}

void
Application::transport_set_speed (float speed)
{
	LOG;
	s_application->data->worker.call_async (boost::bind (&Application::transport_set_speed_internal, s_application, speed));
}

float
Application::transport_get_speed ()
{
	return s_application->data->speed;
}

void
Application::transport_stop ()
{
	transport_set_speed (0);
}

void
Application::transport_play ()
{
	transport_set_speed (1.0);
}

void
Application::transport_set_position (count_t pos)
{
	s_application->data->worker.call_async (boost::bind (&Application::transport_set_position_internal, s_application, pos));
}

count_t
Application::transport_get_position ()
{
	return s_application->data->position;
}

void
Application::transport_set_record (bool record)
{
	s_application->data->worker.call_async (boost::bind (&Application::transport_set_record_internal, s_application, record));
}

bool
Application::transport_get_record ()
{
	return s_application->data->record;
}

AudioFileSP
Application::open_audiofile (const fs::path& p)
{
	AudioFileModuleSPSet modules = get_audiofile_modules ();

	for (AudioFileModuleSPSet::const_iterator i = modules.begin();
			i != modules.end(); ++i)
	{
		AudioFileSP af = (*i)->open (p.string());

		if (af) return af;
	}

	return AudioFileSP();
}

ModuleSPSet
Application::get_modules ()
{
	return s_application->data->m_modules;
}

AudioFileModuleSPSet
Application::get_audiofile_modules ()
{
	return get_modules_of_type<AudioFileModule> (get_modules());
}

AudioDriverModuleSPSet
Application::get_audio_driver_modules ()
{
	return get_modules_of_type<AudioDriverModule> (get_modules());
}

AudioEffectModuleSPSet
Application::get_audio_effect_modules ()
{
	return get_modules_of_type<AudioEffectModule> (get_modules());
}

ArchiveModuleSPSet
Application::get_archive_modules ()
{
	return get_modules_of_type<ArchiveModule> (get_modules());
}

ArchiveSP
Application::create_archive ()
{
	ArchiveModuleSPSet modules = get_archive_modules ();

	if (!modules.empty())
	{
		ArchiveModuleSP mod = *modules.begin();
		return ArchiveSP(mod->create_archive ());
	}
	return ArchiveSP();
}

void
Application::register_types ()
{
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int32_t>(int32_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int64_t>(int64_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<float>(float_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<std::string>(string_type_name)));

	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<ObjectCollection>(collection_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<ObjectSP>(object_ref_type_name)));

	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<AudioTrack>(audio_track_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<MidiTrack>(midi_track_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<AudioSequence>(audio_sequence_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<AudioEvent>(audio_event_type_name)));
}

} // namespace mojo
