#include "application.hpp"

#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>

#include "gleam/utils.hpp"

#include "mojo/core/debug.hpp"
#include "mojo/core/module_utils.hpp"

#include "mojo/typesystem/type_system.hpp"
#include "mojo/typesystem/template_type_factory.hpp"

#include "mojo/core/type_names.hpp"

#include "mojo/application/object_collection.hpp"
#include "mojo/application/audio_track.hpp"
#include "mojo/application/midi_track.hpp"
#include "mojo/application/audio_sequence.hpp"
#include "mojo/application/audio_event.hpp"

#include "mojo/interfaces/audio_file_module.hpp"
#include "mojo/interfaces/audio_driver_module.hpp"
#include "mojo/interfaces/audio_effect_module.hpp"
#include "mojo/interfaces/archive.hpp"
#include "mojo/interfaces/archive_module.hpp"

#include "mojo/fs/filesystem_paths.hpp"
#include "mojo/core/debug.hpp"

#include "application_data.hpp"
#include "audio_track.hpp"

MOJO_DEBUG_DOMAIN(APPLICATION);

#ifndef NDEBUG
namespace {

void
set_debugging_from_env_var ()
{
	using tokenizer = boost::tokenizer<boost::char_separator<char> >;
	boost::char_separator<char> sep (",");
	tokenizer tokens (gleam::getenv("MOJO_DEBUG"), sep);

	for (auto& t : tokens) {
		mojo::debug::set_enabled (
			mojo::debug::get_domain_index(t.c_str()), true);
	}
}

}
#endif

namespace mojo {

mojo::Application&
Application::get_instance ()
{
	static mojo::Application s_instance;
	return s_instance;
}

void
Application::iteration (bool block)
{
	get_instance().data->worker.iteration (block);
}

Application::Application ()
{
	MOJO_DEBUG(APPLICATION);
	data = std::unique_ptr<internal::ApplicationData>(new internal::ApplicationData);

	register_types ();

#ifndef NDEBUG
	set_debugging_from_env_var ();
#endif

	data->m_modules = discover_modules (module_search_path ());
}

Application::~Application ()
{
	MOJO_DEBUG(APPLICATION);
}

void
Application::new_project ()
{
	MOJO_DEBUG(APPLICATION);
	get_instance().data->worker.call_async (boost::bind (&Application::new_project_internal, boost::ref(get_instance())));
}

void
Application::open_project (const std::string& project_file)
{
	MOJO_DEBUG(APPLICATION);
	get_instance().data->worker.call_async (boost::bind (&Application::open_project_internal, boost::ref(get_instance()), project_file));
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
	if (get_instance().data->active_project == p) return;
	get_instance().data->worker.call_async (boost::bind (&Application::set_active_project_internal, boost::ref(get_instance()), p));
}

Project*
Application::get_active_project()
{
	return get_instance().data->active_project;
}

void
Application::close_project (Project* p)
{
	MOJO_DEBUG(APPLICATION);
	get_instance().data->worker.call_async (boost::bind (&Application::close_project_internal, boost::ref(get_instance()), p));
}

signals::connection
Application::connect_project_added (const ProjectAddedFunc& slot)
{
	return get_instance().data->m_project_added.connect(slot);
}

signals::connection
Application::connect_project_removed (const ProjectRemovedFunc& slot)
{
	return get_instance().data->m_project_removed.connect(slot);
}

void
Application::add_track (Project* p, const TrackOptions& options)
{
	MOJO_DEBUG(APPLICATION);
	get_instance().data->worker.call_async (boost::bind (&Application::add_track_internal, boost::ref(get_instance()), p, options));
}

bool
Application::is_audio_track (Track* t)
{
	return dynamic_cast<AudioTrack*>(t);
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
	return get_instance().data->m_modules;
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
