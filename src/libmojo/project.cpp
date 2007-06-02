#include <fstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


// 
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
Project::set_name (const string& new_name)
{
	if (m_name != new_name)
	{
		m_name = new_name;
		m_signal_name_change ();
	}
}

bool
Project::save ()
{
#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG;
#endif

	std::ofstream ofs(m_name.c_str());
	
	// check stream state
	
	// save data to archive
	{
		boost::archive::xml_oarchive oa(ofs);

		// can't pass *this, must be const, can't remember why.
		const Project& project = *this;

		// write class instance to archive
		oa << BOOST_SERIALIZATION_NVP(project);
		// archive and stream closed when destructors are called
	}

	// check stream state?
	return true;
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
		m_signal_destroy ();
	}
}


} // namespace mojo
