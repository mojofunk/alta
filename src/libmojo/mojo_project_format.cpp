
#include <fstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <libmojo/project.hpp>
#include <libmojo/mojo_project_format.hpp>

#include <libmojo/debug.hpp>

namespace mojo {

Project*
MojoProjectFormat::open_project (const fs::path& project_file)
{
#ifdef MOJO_DEBUG
	LOG_MOJO_DEBUG;
#endif

	Project* project = new Project;

	// why does this have to be opened in binary mode again?
	std::ifstream ifs(project_file.string().c_str(), std::ios::binary);

	boost::archive::xml_iarchive ia(ifs);
	
	// try/catch?
	// read class state from archive
	ia >> BOOST_SERIALIZATION_NVP(project);

	return project;
}

void
MojoProjectFormat::save_project (const Project& project, const fs::path& project_file)
{
	std::ofstream ofs(project_file.string().c_str());
	
	// check stream state
	
	/// @todo try/catch exceptions and rethrow
	{
		boost::archive::xml_oarchive oa(ofs);

		// write class instance to archive
		oa << BOOST_SERIALIZATION_NVP(project);
		// archive and stream closed when destructors are called
	}
}

} // namespace mojo
