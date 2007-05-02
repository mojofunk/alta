
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

namespace mojo {

class Project : boost::noncopyable
{
public:

	// factory functions

	// create a new project
	static boost::shared_ptr<Project> create();

public:

	void set_name(const std::string&);

	const std::string& get_name () const;

private:

    /**
	 * This will create temporary project in a temporary
	 * directory until the project is saved.
	 */
    Project();

    ~Project();

	/**
	 * load a project from disk
	 */
	 //project(const string& file_path);

	// member data
	std::string m_name;

private:
	
	struct deleter;
	friend struct deleter;
		
	struct deleter
	{
		void operator()(Project* project) { delete project; }
	};

};

} // namespace mojo

#endif // MOJO_PROJECT_HPP
