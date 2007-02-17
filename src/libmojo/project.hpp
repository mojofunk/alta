
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <string>

#include <boost/shared_ptr.hpp>

namespace mojo {

class project
{
private:
	class impl;
	boost::shared_ptr<impl> m_pimpl;

public:
    
    /**
       path to project 
    */
    //const std::string& path() { return m_path; }
    
    
    /**
	 * This will create temporary project in a temporary
	 * directory until the project is saved.
	 */
    project();

	/*
	 project(const string& path);
	 */

    ~project();

// need a operator== ?

protected:

    /// path to project file.
    //const std::string m_path;
    
};

} // namespace mojo

#endif // MOJO_PROJECT_HPP
