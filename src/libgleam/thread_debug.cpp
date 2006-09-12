
#include <glib.h>

#include <libgleam/thread_debug.hpp>

namespace {

gleam::ThreadMap* s_thread_map = 0;

}

namespace gleam {

ThreadMap& thread_map ()
{
	if(s_thread_map == 0) {

		s_thread_map = new ThreadMap();

	}

	return *s_thread_map;
}

} // namespace gleam
