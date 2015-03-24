
#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/debug/debug.hpp"
#include "mojo/core/system/utils.hpp"
#include "mojo/core/string/compose.hpp"
#endif

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

bool
initialize ()
{
#ifndef NDEBUG
	set_debugging_from_env_var ();
#endif

}

void
terminate ()
{


}

} // namespace mojo
