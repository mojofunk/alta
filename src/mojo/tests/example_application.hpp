
#ifndef MOJO_TEST_EXAMPLE_APPLICATION_H
#define MOJO_TEST_EXAMPLE_APPLICATION_H

#include <mutex>

#include "mojo/mojo.hpp"

class ExampleApplication
{
public: // ctors

	ExampleApplication ();

	~ExampleApplication ();

public: // methods

	void on_project_added (mojo::Project* p);

	void on_project_removed (mojo::Project* p);

	void close_projects ();

private: // member data

	std::set<mojo::Project*>    m_projects;
	std::mutex                  m_mutex;

};

#endif
