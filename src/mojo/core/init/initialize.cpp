
#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/debug/debug.hpp"
#include "mojo/core/system/utils.hpp"
#include "mojo/core/string/compose.hpp"
#include "mojo/core/typesystem/type_names.hpp"
#include "mojo/core/typesystem/type_system.hpp"
#include "mojo/core/typesystem/template_type_factory.hpp"
#endif

MOJO_DEBUG_DOMAIN(CORE_INITIALIZE);

namespace {

std::atomic_uint s_init_count(0);

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

void
register_builtin_types ()
{
	MOJO_DEBUG_MSG(CORE_INITIALIZE, "Registering builtin types");
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int32_t>(int32_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int64_t>(int64_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<float>(float_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<std::string>(string_type_name)));
}

}

namespace mojo {

namespace core {

void
initialize ()
{
	if (++s_init_count != 1) return;

#ifndef NDEBUG
	set_debugging_from_env_var ();
#endif

	MOJO_DEBUG_MSG(CORE_INITIALIZE, "Initializing mojo-core");

	register_builtin_types ();
}

bool
initialized ()
{
	return (s_init_count != 0);
}

void
deinitialize ()
{
	if (--s_init_count != 0) return;

	MOJO_DEBUG_MSG(CORE_INITIALIZE, "Deinitializing mojo-core");

	// deregister_builtin_types
}

} // namespace core

} // namespace mojo
