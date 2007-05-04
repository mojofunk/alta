
#include <fstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "project_format.hpp"

#include "debug.hpp"

namespace mojo {

ProjectFormat::ProjectFormat()
{
#ifdef MOJO_DEBUG
	LOG_MOJO_DEBUG;
#endif

}

ProjectFormat::~ProjectFormat()
{
#ifdef MOJO_DEBUG
	LOG_MOJO_DEBUG;
#endif

}

Project*
ProjectFormat::load_project(const string& file_path)
{
#ifdef MOJO_DEBUG
	LOG_MOJO_DEBUG;
#endif

	Project* project = new Project;

	std::ifstream ifs(file_path.c_str(), std::ios::binary);
	
	boost::archive::xml_iarchive ia(ifs);
	// read class state from archive
	ia >> BOOST_SERIALIZATION_NVP(project);

	return project;
}

bool
ProjectFormat::save_project(const Project& project,
			const string& file_path)
{
#ifdef MOJO_DEBUG
	LOG_MOJO_DEBUG;
#endif

	std::ofstream ofs(file_path.c_str());

	// save data to archive
	{
		boost::archive::xml_oarchive oa(ofs);

		// write class instance to archive
		oa << BOOST_SERIALIZATION_NVP(project);
		// archive and stream closed when destructors are called
	}

	return true;
}

} // namespace mojo
