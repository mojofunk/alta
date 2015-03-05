#ifndef MOJO_OBJECT_H
#define MOJO_OBJECT_H

#ifndef MOJO_APPLICATION_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#include "mojo/core/object/change_set.hpp"
#include "mojo/core/object/properties.hpp"
#include "mojo/core/object/signals.hpp"
#endif

namespace mojo {

class Object
{
	typedef signals::signal<void (const ChangeSet&)> changed_signal_t;
	typedef signals::signal<void ()> destroy_signal_t;

public:
	typedef	changed_signal_t::slot_type changed_slot_t;
	typedef	destroy_signal_t::slot_type destroy_slot_t;
	typedef	signals::connection connection_t;

	// type_name

	virtual void get_properties (Properties& props) const = 0;

	virtual void set_properties (const Properties& props) = 0;

	// bool set_property
	//
	// bool get_property

	connection_t on_changed_signal (const changed_slot_t& slot)
	{ m_changed_signal.connect (slot); }

	void destroy () { m_destroy_signal (); }

	/**
	 * When a reference to an Object is held the holder must
	 * register a functor to drop references when an Object is
	 * forcibly destroyed.
	 *
	 * should this be called dispose? or do we need a separate
	 * dispose handler
	 */
	connection_t on_destroy_signal (const destroy_slot_t& slot)
	{ m_destroy_signal.connect (slot); }

protected:

	virtual ~Object() { }

	changed_signal_t m_changed_signal;
	destroy_signal_t m_destroy_signal;

	void signal_changes (const ChangeSet& changes)
	{
		if (!changes.empty())
		{
			m_changed_signal (changes);
		}
	}
};

} // namespace mojo

#endif // MOJO_OBJECT_H
