/*
    Copyright (C) 2005 Tim Mayberry

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    $Id$
*/

#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h>

//#include "i18n.h" ///@todo use glib i18n
#include "glade_path.hpp"

#include <iostream>

namespace gmojo {

std::string
GladePath::path(const std::string& glade_file)
{
	std::string user_glade_dir = Glib::getenv("GMOJO_GLADE_PATH");
	std::string full_path;
	
	if(!user_glade_dir.empty()) {
		full_path = Glib::build_filename(user_glade_dir, glade_file);
		if(Glib::file_test(full_path, Glib::FILE_TEST_EXISTS)) return full_path;
	}
	
	// check if file ~/.gmojo/glade/glade_file exists.
	std::vector<std::string> path;
	path.push_back(Glib::get_home_dir());
	path.push_back(".gmojo"); // define as a constant somewhere?
	path.push_back("glade");
	path.push_back(glade_file);
	full_path = Glib::build_filename(path);
	
	// temporary debugging
	std::cout << "Path to glade file" << full_path << std::endl;
	
	if(Glib::file_test(full_path, Glib::FILE_TEST_EXISTS)) return full_path;
	
	/*
	  If for some wierd reason the system wide glade file
	  doesn't exist libglademm will throw an exception 
	  so don't bother testing if it exists etc.
	*/
	return Glib::build_filename(GLADE_PATH, glade_file);
}

} // namespace gmojo

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
