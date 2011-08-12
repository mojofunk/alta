#ifndef MOJO_OBJECT
#define MOJO_OBJECT

#include <boost/signals2.hpp>

#include <mojo/core/properties.hpp>

namespace mojo {

class Object
{
	typedef boost::signals2::signal<void (const Properties&)> changed_signal_t;

public:
	typedef	changed_signal_t::slot_type changed_slot_t;
	typedef	boost::signals2::connection connection_t;

	// type_name

	virtual void get_properties (Properties& props) const = 0;

	virtual void set_properties (const Properties& props) = 0;

	// bool set_property
	//
	// bool get_property
	//
	// signal_
	//

	connection_t on_changed_signal (const changed_slot_t& slot)
	{ m_changed_signal.connect (slot); }

protected:

	virtual ~Object() { }

	changed_signal_t m_changed_signal;

};

} // namespace mojo

#endif
