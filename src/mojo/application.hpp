
#ifndef MOJO_APPLICATION_INCLUDED
#define MOJO_APPLICATION_INCLUDED

#include <boost/shared_ptr.hpp>

#include <mojo/project_ptr.hpp>

namespace mojo {

/**
 * I'm not sure what this class should be called but it
 * is intended to hold all the resources that are unique
 * to each process and as such is a singleton. Things like
 * the audio drivers, plugin management and preferences etc.
 */
class Application
{
public:

	// typedefs
	typedef boost::shared_ptr<Application>    ptr;
	typedef boost::weak_ptr<Application>      weak_ptr;

public:

	// singleton constructor
	static boost::shared_ptr<Application> create (int argc, char *argv[]);

	static Application& instance() { return *sm_app; }

private:

	// member data
	static Application* sm_app;

private:
	
	// constructors
    Application (int argc, char *argv[]);
    ~Application();

private:

	// private deleter for shared_ptr
	struct deleter;
	friend struct deleter;

	struct deleter
	{
		void operator()(Application* app) { delete app; sm_app = 0; }
	};

};

} // namespace mojo

#endif
