
#ifndef UI_APP_DATA
#define UI_APP_DATA

#include <set>

#include <boost/shared_ptr.hpp>

#include <mojo/mojo.hpp>

#include "project_windows.hpp"
#include "bus.hpp"

namespace ui {

struct AppData
{
	typedef std::set< boost::shared_ptr<ProjectWindows> > project_windows_set_t;

	project_windows_set_t projects;

        mojo::Session m_session;
        Bus     m_bus;
};

} // namespace ui

#endif
