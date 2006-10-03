
#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h>

//#include "i18n.h" ///@todo use glib i18n
#include "glade_path.hpp"

#include <iostream>

namespace bling {

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

} // namespace bling
