/*
    Copyright (C) 2011 Tim Mayberry

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <sstream>

#include <glibmm/miscutils.h>

#include "mojo/fs/filesystem_paths.hpp"

#include "test_common.hpp"

using namespace std;
using namespace mojo;

Searchpath
test_search_path ()
{
	Searchpath test_path(system_data_search_path());
	return Searchpath(Glib::getenv("MOJO_TEST_PATH")) + test_path;
}

fs::path
new_test_output_dir ()
{
	fs::path tmp_dir(g_get_tmp_dir());
	tmp_dir /= "mojo_test";
	string dir_name;
	do {
		ostringstream oss;
		oss << g_random_int ();
		dir_name = oss.str();
	} while (!fs::create_directories (tmp_dir / dir_name));
	return tmp_dir / dir_name;
}
