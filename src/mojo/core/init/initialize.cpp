static std::atomic<uint32_t> s_init_core_count(0);

#ifndef NDEBUG
void set_debugging_from_env_var()
{
	using tokenizer = boost::tokenizer<boost::char_separator<char>>;
	boost::char_separator<char> sep(",");
	tokenizer tokens(mojo::getenv("MOJO_DEBUG"), sep);

	for (auto& t : tokens) {
		mojo::debug::set_enabled(mojo::debug::get_domain_index(t.c_str()), true);
	}
}
#endif

namespace core {

void initialize()
{
	if (++s_init_core_count != 1) return;

	logging::initialize();

	initialize_loggers();

#ifndef NDEBUG
	set_debugging_from_env_var();
#endif

	M_LOG(Init, "Initializing mojo-core");

#ifdef MOJO_WINDOWS
	mmcss::initialize();
#endif

	types::initialize();
}

bool initialized()
{
	return (s_init_core_count != 0);
}

void deinitialize()
{
	if (--s_init_core_count != 0) return;

	M_LOG(Init, "Deinitializing mojo-core");

#ifdef MOJO_WINDOWS
	mmcss::deinitialize();
#endif

	types::deinitialize();

	logging::deinitialize ();
}

} // namespace core
