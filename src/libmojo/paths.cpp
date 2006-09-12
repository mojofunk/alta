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

#include <glibmm/miscutils.h>

#include <libmojo/paths.hpp>
#include <libmojo/paths_system.hpp>
#include <libmojo/paths_user.hpp>

namespace mojo {

const path_string
paths::mojo_env_path_string ()
{
	return path_string(Glib::getenv("ARDOUR_PATH"));
}

const path_string
paths::config_path_string ()
{
	return mojo_env_path() + path_string(paths::user::mojo_dir()) + paths::system::config_path_string();
}

const path_string
paths::pixmap_path_string ()
{
	return mojo_env_path_string() + paths::system::pixmap_path_string ();
}

} // namespace mojo

