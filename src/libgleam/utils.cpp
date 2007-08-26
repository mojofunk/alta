
#include <glib.h>

#include <libgleam/utils.hpp>

namespace gleam {

string
getenv(const string& name)
{
	return g_getenv( name.c_str() );
}

}
