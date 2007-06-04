
#include <mojo/project.hpp>
#include <mojo/project_format.hpp>

#include <mojo/debug/debug.hpp>

namespace mojo {

Project::Project()
	:
		m_project_file()
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
Project::save_as (ProjectFormat::ptr format,
		const fs::path& directory, const fs::path& name)
{
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
