
#ifndef MOJO_APPLICATION_INCLUDED
#define MOJO_APPLICATION_INCLUDED

#include <boost/shared_ptr.hpp>

#include <mojo/type_system_ptr.hpp>

namespace mojo {

class Application;

typedef boost::shared_ptr<Application>    ApplicationSPtr;
typedef boost::weak_ptr<Application>      ApplicationWPtr;

/**
 * I'm not sure what this class should be called but it
 * is intended to hold all the resources that are unique
 * to each process and as such is a singleton. Things like
 * the audio drivers, plugin management and preferences etc.
 */
class Application
{
public:

	// singleton constructor
	static ApplicationSPtr init (int argc, char *argv[]);

	static Application& instance() { return *s_app; }

private:

	// member data
	static Application* s_app;

	TypeSystemSPtr m_type_system;

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
		void operator()(Application* app)
		{ delete app; s_app = 0; }
	};

};

} // namespace mojo

#endif
