#ifndef MOJO_CORE_DEBUG_H
#define MOJO_CORE_DEBUG_H

namespace debug
{

DebugRegistry&
get_registry();

uint32_t
get_domain_index(const char* domain_name);

bool
get_enabled(uint32_t domain_index);

void
set_enabled(uint32_t domain_index, bool enable);

void
log_message(const char* file,
            int line,
            uint32_t domain,
            const std::string& str);

} // namespace debug

#ifdef MOJO_ENABLE_DEBUG_LOGGING

#define MOJO_DEBUG_DOMAIN(domain_name)                                         \
	namespace                                                                     \
	{                                                                             \
	uint32_t domain_name = mojo::debug::get_domain_index(#domain_name);           \
	}

#define MOJO_DEBUG_MSG(domain, str)                                            \
	if (mojo::debug::get_enabled(domain)) {                                       \
		mojo::debug::log_message(__FILE__, __LINE__, domain, str);                   \
	}

#define MOJO_DEBUG(domain)                                                     \
	if (mojo::debug::get_enabled(domain)) {                                       \
		mojo::debug::log_message(__FILE__, __LINE__, domain, "");                    \
	}

#define MOJO_DEBUG_TIMING_START(domain, td)                                    \
	if (mojo::debug::get_enabled(domain)) {                                       \
		td.start_timing();                                                           \
	}
#define MOJO_DEBUG_TIMING_ADD_ELAPSED(domain, td)                              \
	if (mojo::debug::get_enabled(domain)) {                                       \
		td.add_elapsed();                                                            \
	}
#define MOJO_DEBUG_TIMING_RESET(domain, td)                                    \
	if (mojo::debug::get_enabled(domain)) {                                       \
		td.reset();                                                                  \
	}

#else // debug logging disabled

#define MOJO_DEBUG_DOMAIN(domain_name)
#define MOJO_DEBUG_MSG(domain, str)
#define MOJO_DEBUG(domain)

#define MOJO_DEBUG_TIMING_START(domain, td)
#define MOJO_DEBUG_TIMING_ADD_ELAPSED(domain, td)
#define MOJO_DEBUG_TIMING_RESET(domain, td)

#endif

#endif // MOJO_CORE_DEBUG_H
