Application* Application::s_instance = nullptr;

M_DEFINE_LOGGER(Application);

Application::Application()
{
	core::initialize();
	s_instance = this;

	M_GET_LOGGER(Application);

	data =
	    std::unique_ptr<internal::ApplicationData>(new internal::ApplicationData);

	register_types();

	data->m_modules = discover_modules(module_search_path());
}

Application::~Application()
{
	data.reset();
	s_instance = nullptr;
	core::deinitialize();
}

void Application::iteration(bool block)
{
	s_instance->data->worker.iteration(block);
}

void Application::new_project()
{
	M_LOG_CALL(Application);
	s_instance->data->worker.call_async(
	    boost::bind(&Application::new_project_internal, boost::ref(*s_instance)));
}

void Application::open_project(const std::string& project_file)
{
	M_LOG_CALL(Application);
	s_instance->data->worker.call_async(
	    boost::bind(&Application::open_project_internal,
	                boost::ref(*s_instance),
	                project_file));
}

void Application::save_project_as(Project*, const std::string& filename)
{
}

void Application::save_project(Project*)
{
}

void Application::set_active_project(Project* p)
{
	if (s_instance->data->active_project == p) return;
	s_instance->data->worker.call_async(boost::bind(
	    &Application::set_active_project_internal, boost::ref(*s_instance), p));
}

Project* Application::get_active_project()
{
	return s_instance->data->active_project;
}

void Application::close_project(Project* p)
{
	M_LOG_CALL(Application);
	s_instance->data->worker.call_async(boost::bind(
	    &Application::close_project_internal, boost::ref(*s_instance), p));
}

signals::connection
Application::connect_project_added(const ProjectAddedFunc& slot)
{
	return s_instance->data->m_project_added.connect(slot);
}

signals::connection
Application::connect_project_removed(const ProjectRemovedFunc& slot)
{
	return s_instance->data->m_project_removed.connect(slot);
}

void Application::add_track(Project* p, const TrackOptions& options)
{
	M_LOG_CALL(Application);
	s_instance->data->worker.call_async(boost::bind(
	    &Application::add_track_internal, boost::ref(*s_instance), p, options));
}

bool Application::is_audio_track(Track* t)
{
	return dynamic_cast<AudioTrack*>(t);
}

AudioFileSP Application::open_audiofile(const fs::path& p)
{
	AudioFileModuleSPSet modules = get_audiofile_modules();

	for (auto const& module : modules) {
		AudioFileSP af = module->open(p.string());
		if (af) return af;
	}

	return AudioFileSP();
}

ModuleSPSet Application::get_modules()
{
	return s_instance->data->m_modules;
}

AudioFileModuleSPSet Application::get_audiofile_modules()
{
	return get_modules_of_type<AudioFileModule>(get_modules());
}

AudioDriverModuleSPSet Application::get_audio_driver_modules()
{
	return get_modules_of_type<AudioDriverModule>(get_modules());
}

AudioEffectModuleSPSet Application::get_audio_effect_modules()
{
	return get_modules_of_type<AudioEffectModule>(get_modules());
}

MIDIDriverModuleSPSet Application::get_midi_driver_modules()
{
	return get_modules_of_type<MIDIDriverModule>(get_modules());
}

ArchiveModuleSPSet Application::get_archive_modules()
{
	return get_modules_of_type<ArchiveModule>(get_modules());
}

ArchiveSP Application::create_archive()
{
	ArchiveModuleSPSet modules = get_archive_modules();

	if (!modules.empty()) {
		ArchiveModuleSP mod = *modules.begin();
		return ArchiveSP(mod->create_archive());
	}
	return ArchiveSP();
}

void Application::register_types()
{
	types::register_type(TypeFactorySP(new TemplateTypeFactory<ObjectCollection>(
	    TypeNames::collection_type_name)));
	types::register_type(TypeFactorySP(
	    new TemplateTypeFactory<ObjectSP>(TypeNames::object_ref_type_name)));

	types::register_type(TypeFactorySP(
	    new TemplateTypeFactory<AudioTrack>(TypeNames::audio_track_type_name)));
	types::register_type(TypeFactorySP(
	    new TemplateTypeFactory<MidiTrack>(TypeNames::midi_track_type_name)));
	types::register_type(TypeFactorySP(new TemplateTypeFactory<AudioSequence>(
	    TypeNames::audio_sequence_type_name)));
	types::register_type(TypeFactorySP(
	    new TemplateTypeFactory<AudioEvent>(TypeNames::audio_event_type_name)));
}
