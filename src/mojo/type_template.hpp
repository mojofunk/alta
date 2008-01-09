
#ifndef MOJO_TYPE_TEMPLATE_INCLUDED
#define MOJO_TYPE_TEMPLATE_INCLUDED

#include <boost/shared_ptr.hpp>

#include <mojo/type.hpp>

namespace mojo {

template <class T>
class TypeTemplate : public Type
{
public:

	TypeTemplate (const std::string& type_name)
		: m_type_name(type_name) { }

	virtual std::string type_name () const { return m_type_name; }

	virtual boost::any create () const
	{
		T instance;
		return boost::any(instance);
	}

	virtual const std::type_info& type_info () const
	{
		return typeid(T);
	}

private:

	const std::string m_type_name;

};

template <class T>
class TypeTemplate<boost::shared_ptr<T> > : public Type
{
public:

	TypeTemplate (const std::string& type_name)
		: m_type_name(type_name) { }

	virtual std::string type_name () const { return m_type_name; }

	virtual boost::any create () const
	{
		return boost::any(boost::shared_ptr<T>(new T));
	}

	virtual const std::type_info& type_info () const
	{
		return typeid(T);
	}

private:

	const std::string m_type_name;

};

}

#endif
