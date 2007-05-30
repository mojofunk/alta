
#include <libmojo/project.hpp>

#include <libmojo/debug.hpp>

namespace mojo {

Project::Project()
	: m_name("")
{
#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG;
#endif
}

Project::~Project()
{
#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG;
#endif
}

void
Project::close()
{
	bool close = m_signal_close ();

#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG << "signal_close returned" << close;
#endif

	if(close)
	{
		m_signal_destroy ();
	}
}


} // namespace mojo
