MOJO_DEBUG_DOMAIN(CORE_INITIALIZE);

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

#ifndef NDEBUG
	set_debugging_from_env_var();
#endif

	MOJO_DEBUG_MSG(CORE_INITIALIZE, "Initializing mojo-core");

	types::initialize();
}

bool initialized()
{
	return (s_init_core_count != 0);
}

void deinitialize()
{
	if (--s_init_core_count != 0) return;

	MOJO_DEBUG_MSG(CORE_INITIALIZE, "Deinitializing mojo-core");

	types::deinitialize();
}

} // namespace core
