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

#ifndef ARDOUR_SYSTEM_PATHS_HEADER
#define ARDOUR_SYSTEM_PATHS_HEADER

#include <string>

#include <pbd/path.h>

namespace ARDOUR {

using std::string;
using PBD::Path;

namespace SystemPaths {

Path data_path ();

const Path config_path ();

const Path module_path ();

const Path pixmap_path ();

const Path template_path ();

// XXX expose?
//Path system_data_path();

} // namespace SystemPaths

} // namespace ARDOUR

#endif // ARDOUR_SYSTEM_PATHS_HEADER
