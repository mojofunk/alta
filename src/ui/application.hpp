
#ifndef GMOJO_APPLICATION_INCLUDED
#define GMOJO_APPLICATION_INCLUDED

#include <string>

#include <gtkmm.h>

namespace gmojo {

using std::string;

class Application : public sigc::trackable
{
public:

    Application (int argc, char *argv[]);
    
    virtual ~Application();
    
    static Application& instance();
    
    virtual void run();
    
    /**
      must check the state of each open project,
      if state is dirty then ask the user if they
      want to save the project.
    */
    virtual void quit();
    
    /// all new projects are created in a 
    /// temp directory
    /// activate new project dialogue.
    void new_project();
    
    /// activate open project dialogue.
    void open_project();
    
protected:

    void open_project(const string& path_to_file);
    
    static Application* s_m_app;
        
    /// project agnostic top level dialogs

    // new/open project dialog

    // about dialog
    // preferences dialog
    // tool

    // edit buffer cut/paste


};

} // namespace gmojo

#endif // GMOJO_APPLICATION_INCLUDED
