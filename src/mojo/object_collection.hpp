
#ifndef MOJO_OBJECT_COLLECTION_INCLUDED
#define MOJO_OBJECT_COLLECTION_INCLUDED

#include <list>

#include <mojo/object_ptr.hpp>

namespace mojo {

class ObjectCollection
{
public:

	typedef std::list<ObjectSPtr>::iterator        iterator;
	typedef std::list<ObjectSPtr>::const_iterator  const_iterator;

public:

	template<class ContainerType>
	ObjectCollection (const ContainerType& container)
		: m_list(container.begin(), container.end())
	{ }

	ObjectCollection() { }

	iterator begin () { return m_list.begin(); }

	const_iterator begin () const { return m_list.begin(); }

	iterator end () { return m_list.end(); }

	const_iterator end() const { return m_list.end(); }


protected:

	std::list<ObjectSPtr> m_list;

};

} // namespace mojo

#endif
