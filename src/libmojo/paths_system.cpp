/*
   Copyright (C) 2006 Tim Mayberry

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA  02110-1301, USA.
*/

#include <glib.h>

#include <glibmm/miscutils.h>

#include <ardour/system_paths.h>
#include <ardour/dir_names.h>

#include "debug.h"

namespace ARDOUR {

static Path
system_data_path ()
{
	Path tmp;
	const char * const * dirs;

	dirs = g_get_system_data_dirs ();

	if (dirs == NULL) return tmp;
	
	for (int i = 0; dirs[i] != NULL; i++) {
		tmp += dirs[i];
	}

#ifdef ARDOUR_DEBUG_EXTRA
	LOG_ARDOUR_DEBUG << tmp.path_string();
#endif

	return tmp;
}

static Path
system_config_path ()
{
	Path tmp;
	const char * const * dirs;

	dirs = g_get_system_config_dirs ();

	if (dirs == NULL) return tmp;
	
	for (int i = 0; dirs[i] != NULL; i++) {
		tmp += dirs[i];
	}

#ifdef ARDOUR_DEBUG_EXTRA
	LOG_ARDOUR_DEBUG << tmp.path_string();
#endif

	return tmp;
}

Path
SystemPaths::data_path ()
{
#ifdef WITH_STATIC_PATHS
	return Glib::build_filename (DATA_DIR, ardour_dir_name);
#else
	return system_data_path().add_subdirectory_to_path(ardour_dir_name);
#endif
}

const Path
SystemPaths::config_path ()
{
#ifdef WITH_STATIC_PATHS
	return Glib::build_filename (CONFIG_DIR, ardour_dir_name);
#else
	return system_config_path().add_subdirectory_to_path(ardour_dir_name);
#endif
}

const Path
SystemPaths::module_path ()
{
#ifdef WITH_STATIC_PATHS
	return Glib::build_filename (MODULE_DIR, ardour_dir_name);
#else
	// XXX todo
	return Path("");
#endif
}

const Path
SystemPaths::pixmap_path ()
{
	return data_path().add_subdirectory_to_path(pixmap_dir_name);
}

const Path
SystemPaths::template_path ()
{
	return data_path().add_subdirectory_to_path(template_dir_name);
}

} // namespace ARDOUR
