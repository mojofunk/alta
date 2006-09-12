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

#include <boost/filesystem/operations.hpp>

#include "libmojo/paths_user.hpp"
#include "libmojo/dir_names.hpp"

namespace mojo {

namespace paths {

namespace user {

static const char* const mojo_dir_name = ".mojo";

static const char* const preset_dir_name = "rdf";

static const char* const vst_dir_name = ".vst";

static const char* const ladspa_dir_name = ".ladspa";
	
static const path
home_dir ()
{
	path home_dir(Glib::get_home_dir());

	if(home_dir.empty()) {

#ifdef MOJO_DEBUG
		LOG_MOJO_CRITICAL
			<< "Could not locate home directory for user"
			<< Glib::get_user_name();
#endif

	}

	return home_dir;
}

const path
mojo_dir()
{
	path mojo_dir ( home_dir() / mojo_dir_name );
	create_directory(mojo_dir);
	return mojo_dir;    
}

const path
vst_dir ()
{
	path vst_dir = Glib::build_filename ( home_dir(), vst_dir_name );
	PBD::ensure_directory_exists (vst_dir);
	return vst_dir;
	
}

const path
vst_preset_dir ()
{
	path vst_preset_dir = Glib::build_filename ( vst_dir(), preset_dir_name );
	PBD::ensure_directory_exists (vst_preset_dir);
	return vst_preset_dir;
}

const path
ladspa_dir ()
{
	path ladspa_dir = Glib::build_filename ( home_dir(), ladspa_dir_name );
	PBD::ensure_directory_exists (ladspa_dir);
	return ladspa_dir;
}

const path
ladspa_preset_dir ()
{
	path ladspa_preset_dir = Glib::build_filename ( ladspa_dir(), preset_dir_name );
	PBD::ensure_directory_exists (ladspa_preset_dir);
	return ladspa_preset_dir;
}

} // namespace user

} // namespace paths

} // namespace mojo
