#ifndef MOJO_OBJECT_INCLUDED
#define MOJO_OBJECT_INCLUDED

#include <ark/object.hpp>

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>

namespace mojo {

class Object : public ark::Object
{
public:

	typedef boost::signal<void ()> destroy_signal_t;

public:

	/**
	 * Destroy the object instance, this will cause 
	 * the slots registered with on_signal_destroy to be
	 * called.
	 */
	void destroy ()
	{
		m_signal_destroy ();
		// refcount should now be zero and class destructor
		// called unless there is a reference being held.
	}

	/**
	 * All holders of a reference to this object are required
	 * to register a callback that will be called in the event
	 * that destroy is called, at which point they must drop
	 * the reference.
	 *
	 * I don't think a connection object should be returned to
	 * the caller as the destroy signal indicates to a reference
	 * holder to drop thier reference, if they could disconnect
	 * if defeats the purpose of calling destroy ()
	 * 
	 * This should also take a bus so that the handler is called
	 * in an appropriate thread context.
	 */
	void on_destroy (const destroy_signal_t::slot_type& handler)
	{ m_signal_destroy.connect(handler);}

public:

	virtual void get_properties (ark::Properties& props) const = 0;

	virtual void set_properties (const ark::Properties& props) = 0;

protected:
	
	destroy_signal_t m_signal_destroy;

};

}

#endif
