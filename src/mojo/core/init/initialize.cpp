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

M_DEFINE_LOGGER(INIT);
M_DEFINE_LOGGER(RUN_LOOP);
M_DEFINE_LOGGER(STRING_CONVERT);

static void initialize_loggers ()
{
	INIT = logging::make_logger("Init");
	RUN_LOOP = logging::make_logger("RunLoop");
	STRING_CONVERT = logging::make_logger("StringConvert");
}

static void deinitialize_loggers ()
{
	INIT.reset();
	RUN_LOOP.reset();
	STRING_CONVERT.reset();
}

void initialize()
{
	if (++s_init_core_count != 1) return;

	logging::initialize();
	logging::add_sink(std::make_shared<logging::OStreamSink>());

	initialize_loggers();

#ifndef NDEBUG
	set_debugging_from_env_var();
#endif

	M_LOG(INIT, "Initializing mojo-core");

	types::initialize();
}

bool initialized()
{
	return (s_init_core_count != 0);
}

void deinitialize()
{
	if (--s_init_core_count != 0) return;

	M_LOG(INIT, "Deinitializing mojo-core");

	types::deinitialize();

	deinitialize_loggers();

	logging::deinitialize ();
}

} // namespace core
