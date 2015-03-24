
#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/debug/debug.hpp"
#include "mojo/core/system/utils.hpp"
#include "mojo/core/string/compose.hpp"
#endif

MOJO_DEBUG_DOMAIN(CORE_INITIALIZER);

#ifndef NDEBUG
namespace {

void
set_debugging_from_env_var ()
{
	using tokenizer = boost::tokenizer<boost::char_separator<char> >;
	boost::char_separator<char> sep (",");
	tokenizer tokens (mojo::getenv("MOJO_DEBUG"), sep);

	for (auto& t : tokens) {
		mojo::debug::set_enabled (
			mojo::debug::get_domain_index(t.c_str()), true);
	}
}

}
#endif

namespace mojo {

// Possible issue with static init order?
std::atomic_uint CoreInitializer::m_init_count(0);

CoreInitializer::CoreInitializer ()
{
	// check if std::atomic is lock free
	// and throw?

	if (++m_init_count == 1) {
		initialize ();
	}
}

CoreInitializer::~CoreInitializer ()
{
	if (--m_init_count == 0) {
		deinitialize ();
	}
}

bool
CoreInitializer::initialized ()
{
	return (m_init_count != 0);
}

bool
CoreInitializer::initialize ()
{
#ifndef NDEBUG
	set_debugging_from_env_var ();
#endif

	MOJO_DEBUG_MSG(CORE_INITIALIZER, "Initializing mojo-core");

	// register_builtin_types
}

void
CoreInitializer::deinitialize ()
{
	MOJO_DEBUG_MSG(CORE_INITIALIZER, "Deinitializing mojo-core");

	// deregister_builtin_types

}

} // namespace mojo
