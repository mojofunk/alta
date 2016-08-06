#ifndef MOJO_CHANGE_SET_H
#define MOJO_CHANGE_SET_H

/**
 * A ChangeSet is a collection of related property changes
 *
 * Why can't this just be std::set<Change>? do we want ChangeSet
 * to inherit from Object? I don't think so.
 */
class ChangeSet {
public:
	typedef std::set<Change> container_t;
	typedef container_t::iterator iterator;
	typedef container_t::const_iterator const_iterator;

public: // iterators
	iterator begin() { return m_changes.begin(); }
	iterator end() { return m_changes.end(); }
	const_iterator end() const { return m_changes.end(); }
	const_iterator begin() const { return m_changes.begin(); }

public:
	ChangeSet(){};

	ChangeSet(const Change& change) { insert(change); }

	bool insert(const Change& change)
	{
		if (!change) return false;

		// TODO check insertion was successful
		m_changes.insert(change);
		return true;
	}

	bool empty() const { return m_changes.empty(); }

private:
	container_t m_changes;
};

#endif // MOJO_CHANGE_SET_H
