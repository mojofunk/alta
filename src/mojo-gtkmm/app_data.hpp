
#ifndef UI_APP_DATA
#define UI_APP_DATA

#include <set>

#include <boost/shared_ptr.hpp>

#include <mojo/mojo.hpp>

#include "project_objects.hpp"
#include "session_event_handler.hpp"

namespace ui {

struct AppData
{
	typedef std::set< boost::shared_ptr<ProjectObjects> > project_objects_set_t;

	project_objects_set_t project_objs;

        mojo::Session m_session;
        SessionEventHandler     m_session_event_handler;
};

} // namespace ui

#endif
