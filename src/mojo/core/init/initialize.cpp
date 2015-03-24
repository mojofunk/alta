
#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/debug/debug.hpp"
#include "mojo/core/system/utils.hpp"
#include "mojo/core/string/compose.hpp"
#include "mojo/core/typesystem/type_system.hpp"
#endif

MOJO_DEBUG_DOMAIN(CORE_INITIALIZE);

namespace {

std::atomic_uint s_init_core_count(0);

using namespace mojo;

#ifndef NDEBUG
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
#endif

}

namespace mojo {

namespace core {

void
initialize ()
{
	if (++s_init_core_count != 1) return;

#ifndef NDEBUG
	set_debugging_from_env_var ();
#endif

	MOJO_DEBUG_MSG(CORE_INITIALIZE, "Initializing mojo-core");

	TypeSystem::initialize ();
}

bool
initialized ()
{
	return (s_init_core_count != 0);
}

void
deinitialize ()
{
	if (--s_init_core_count != 0) return;

	MOJO_DEBUG_MSG(CORE_INITIALIZE, "Deinitializing mojo-core");

	TypeSystem::deinitialize ();
}

} // namespace core

} // namespace mojo
