#ifndef MOJO_OBJECT_INCLUDED
#define MOJO_OBJECT_INCLUDED

#include <boost/signal.hpp>

#include <libgleam/atomic_counter.hpp>

namespace mojo {

class Object
{
protected:

	Object ();

	virtual ~Object ();

public:

	void ref ();

	void unref ();

	boost::signal<void ()>& signal_destroy()
	{ return m_signal_destroy; }

protected:

	// drop all references and call derived
	// class dispose() method
	// virtual void dispose();

	// signal to drop all references
	boost::signal<void ()> m_signal_destroy;

private:

	gleam::atomic_counter m_ref_count;
};

}

#endif
