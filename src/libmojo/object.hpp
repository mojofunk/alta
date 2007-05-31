#ifndef MOJO_OBJECT_INCLUDED
#define MOJO_OBJECT_INCLUDED

#include <boost/signal.hpp>

#include <libgleam/atomic_counter.hpp>

namespace mojo {

class Object
{
protected:

	Object ();

	// destroy any member data that has been allocated by this
	// class etc.
	virtual ~Object ();

public:

	void ref ();

	void unref ();

	// manually destroy the object instance, this will
	// cause Object::signal_destroy() to be emitted. Which
	// signals all reference holders to drop there references
	// which should mean(unless there is a leak) the reference
	// count drops to zero and dispose is called.
	virtual void destroy() = 0;

	boost::signal<void ()>& signal_destroy()
	{ return m_signal_destroy; }

protected:

	// drop all references and call derived
	// class dispose() method
	virtual void dispose() = 0;

	// signal to drop all references
	boost::signal<void ()> m_signal_destroy;

private:

	gleam::atomic_counter m_ref_count;
};

}

#endif
