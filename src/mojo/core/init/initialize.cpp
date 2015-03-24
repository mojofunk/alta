
#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/debug/debug.hpp"
#include "mojo/core/system/utils.hpp"
#include "mojo/core/string/compose.hpp"
#include "mojo/core/typesystem/type_system.hpp"
#endif

MOJO_DEBUG_DOMAIN(CORE_INITIALIZER);

#ifndef NDEBUG
namespace {

using namespace mojo;

void
set_debugging_from_env_var ()
{
	using tokenizer = boost::tokenizer<boost::char_separator<char> >;
	boost::char_separator<char> sep (",");
	tokenizer tokens (mojo::getenv("MOJO_DEBUG"), sep);

	MOJO_DEBUG_MSG(CORE_INITIALIZER,
		mojo::compose("MOJO_DEBUG = %", mojo::getenv("MOJO_DEBUG")));

	for (auto& t : tokens) {
		mojo::debug::set_enabled (
			mojo::debug::get_domain_index(t.c_str()), true);
	}
}

void
register_builtin_types ()
{
	MOJO_DEBUG_MSG(CORE_INITIALIZER, "Registering builtin types");
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int32_t>(int32_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int64_t>(int64_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<float>(float_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<std::string>(string_type_name)));
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

	register_builtin_types ();
}

void
CoreInitializer::deinitialize ()
{
	MOJO_DEBUG_MSG(CORE_INITIALIZER, "Deinitializing mojo-core");

	// deregister_builtin_types

}

} // namespace mojo
