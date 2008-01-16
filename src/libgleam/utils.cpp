
#include <glib.h>

#include <libgleam/utils.hpp>

namespace gleam {

string
getenv(const string& name)
{
	const char* const env = g_getenv( name.c_str() );
	if(env) return env;
	else return string();
}

}
