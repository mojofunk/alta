
#include <mojo/project.hpp>
#include <mojo/project_format.hpp>

#include <mojo/debug.hpp>

namespace mojo {

Project::Project()
	:
		m_project_file(),
		m_format(0)
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
Project::dispose ()
{
	if (m_format)
	{
		m_format->unref ();
	}
}

void
Project::save ()
{

	if(!m_format)
	{
		throw;
	}

	try
	{
		m_format->save_project (*this, m_project_file);
	}
	catch (...)
	{

#ifdef MOJO_DEBUG_EXTRA
		LOG_MOJO_DEBUG;
#endif

	}

}

void
Project::save_as (ProjectFormat* format,
		const fs::path& directory, const fs::path& name)
{

	if(m_format)
	{
		m_format->unref ();
		m_format = 0;
	}

	format->ref();
	m_format = format;

	m_project_file = directory / name; // + format->extension ();

	// move project files to directory etc

	save ();

}

void
Project::close ()
{
	bool close = m_signal_close ();

#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG << "signal_close returned" << close;
#endif

	if(close)
	{
		destroy ();
	}
}


} // namespace mojo
