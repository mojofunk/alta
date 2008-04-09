
#ifndef UI_APP_DATA
#define UI_APP_DATA

#include <boost/shared_ptr.hpp>

#include "project.hpp"
#include "project_windows.hpp"

namespace ui {

struct AppData
{
	typedef std::map<boost::shared_ptr<Project>, boost::shared_ptr<ProjectWindows> > project_map_t;

	project_map_t projects;
};

} // namespace ui

#endif
