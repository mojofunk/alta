#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_private_macros
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <iostream>
#include <string>

#include "mojo/core/object/private_macros.hpp"

class ApplicationPrivate;

class Application {
public:
	static std::string directory_path();
	static std::string file_path();

	static std::string name();
	static std::string executable_name();

	static void initialize();
	static void deinitialize();

private:
	Application();

private:
	static Application* instance;

	std::unique_ptr<ApplicationPrivate> d_ptr;

	M_DECLARE_PRIVATE(Application)
};

class ApplicationPrivate {
public:
	ApplicationPrivate()
	    : m_directory_path("private_test_directory_path")
	    , m_name("private_test_name")
	    , m_executable_name("private_test_executable_name")
	{
	}

	std::string m_directory_path;
	std::string m_name;
	std::string m_executable_name;

	std::string file_path()
	{
		// would need to be a path separator etc
		return m_directory_path + m_executable_name;
	}
};

Application* Application::instance;

Application::Application()
    : d_ptr(new ApplicationPrivate())
{
}

void Application::initialize()
{
	assert(!instance);
	instance = new Application;
}

void Application::deinitialize()
{
	delete instance;
}

std::string Application::directory_path()
{
	ApplicationPrivate* d = instance->d_ptr.get();
	return d->m_directory_path;
}

std::string Application::file_path()
{
	ApplicationPrivate* d = instance->d_ptr.get();
	return d->file_path();
}

std::string Application::name()
{
	ApplicationPrivate* d = instance->d_ptr.get();
	return d->m_name;
}

std::string Application::executable_name()
{
	ApplicationPrivate* d = instance->d_ptr.get();
	return d->m_executable_name;
}

BOOST_AUTO_TEST_CASE(private_no_inheritance_test)
{
	Application::initialize();

	std::cout << Application::name() << std::endl;
	std::cout << Application::directory_path() << std::endl;
	std::cout << Application::file_path() << std::endl;
	std::cout << Application::executable_name() << std::endl;

	Application::deinitialize();
}

class BasePrivate;

class Base {
protected:
	Base(BasePrivate*);

	virtual ~Base() {}

protected:
	std::unique_ptr<BasePrivate> d_ptr;

	M_DECLARE_PRIVATE(Base)
};

class BasePrivate {
public:
	virtual ~BasePrivate() = 0;

public:
	Base* q_ptr;

private:
	M_DECLARE_PUBLIC(Base)
public:
};

BasePrivate::~BasePrivate()
{
}

Base::Base(BasePrivate* priv_ptr)
    : d_ptr(priv_ptr)
{
	d_ptr->q_ptr = this;
}

class DerivedPrivate;

class Derived : public Base {
	M_DECLARE_PRIVATE(Derived)
protected:
	Derived(DerivedPrivate*);

public:
	Derived();
};

class DerivedPrivate : public BasePrivate {
	M_DECLARE_PUBLIC(Derived)
public:
};

Derived::Derived()
    : Base(new DerivedPrivate)
{
}

Derived::Derived(DerivedPrivate* priv)
    : Base(priv)
{
}

BOOST_AUTO_TEST_CASE(private_inheritance_test)
{
	Derived derived;
}
