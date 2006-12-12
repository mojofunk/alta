
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <string>

#include <libmojo/project_dir.hpp>

namespace mojo {

class Project
{
public:
    
    /**
       path to project 
    */
    //const std::string& path() { return m_path; }
    
    
    /**
       
    */
    Project();

    ~Project();
    

protected:

    /// path to project file.
    //const std::string m_path;
    
};

} // namespace mojo

#endif // MOJO_PROJECT_HPP
