
#ifndef BLING_GLADE_PATH_INCLUDED
#define BLING_GLADE_PATH_INCLUDED

#include <string>

namespace bling {

struct GladePath {
    
	/**
	   @return Path to glade file.
	   
	   XXX subject to change upon discussion.
       
	   glade files are currently looked for in
	   three possible directories in this order.
       
	   In the directory defined in the environment
	   variable ARDOUR_GLADE_PATH
       
	   In the users .ardour/glade directory.
	   
	   In the system defined glade path.
	*/
	static std::string
	path(const std::string& glade_filename);
    
};

} // namespace bling

#endif // BLING_GLADE_PATH_INCLUDED
