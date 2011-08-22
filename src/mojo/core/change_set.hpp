
#ifndef MOJO_CHANGE_SET
#define MOJO_CHANGE_SET

#include <set>

#include "change.hpp"

namespace mojo {

/**
 * A ChangeSet is a collection of related property changes
 */
class ChangeSet
{
public:
	typedef std::set<Change>                container_t;
	typedef container_t::iterator           iterator;
	typedef container_t::const_iterator     const_iterator;

public: // iterators

	iterator begin () { return m_changes.begin(); }
	iterator end () { return m_changes.end(); }
	const_iterator end () const { return m_changes.end(); }
	const_iterator begin () const { return m_changes.begin(); }

public:

	ChangeSet () { };

	ChangeSet (const Change& change)
	{
		insert (change);
	}

	bool insert (const Change& change)
	{
		if (!change) return false;

		m_changes.insert (change);
	}

	bool empty () const
	{
		return m_changes.empty ();
	}

private:

	container_t m_changes;

};

} // namespace mojo

#endif
