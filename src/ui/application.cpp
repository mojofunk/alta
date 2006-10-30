
#include "application.hpp"

namespace gmojo {

Application* Application::s_m_app;

Application::Application (int argc, char *argv[])
{
    if(s_m_app) {
    
        // throw exception
    } else {
	s_m_app = this;
    }    
}

Application::~Application()
{


}

void
Application::run()
{
	// run splash
}

void
Application::quit()
{

}

void
Application::new_project()
{


}

void
Application::open_project()
{
    


}

void
Application::open_project(const string& path_to_file)
{
    
    
}

} // namespace gmojo
