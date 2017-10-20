#ifndef MOJO_OBJECT_COLLECTION_H
#define MOJO_OBJECT_COLLECTION_H

class ObjectCollection
{
public:
	typedef std::list<ObjectSP> container_t;
	typedef container_t::iterator iterator;
	typedef container_t::const_iterator const_iterator;

public:
	template <class ContainerType>
	ObjectCollection(const ContainerType& container)
	    : m_list(container.begin(), container.end())
	{
	}

	ObjectCollection() {}

	iterator begin() { return m_list.begin(); }

	const_iterator begin() const { return m_list.begin(); }

	iterator end() { return m_list.end(); }

	const_iterator end() const { return m_list.end(); }

protected:
	container_t m_list;
};

#endif // MOJO_OBJECT_COLLECTION_H
