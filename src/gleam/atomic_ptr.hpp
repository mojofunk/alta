#ifndef GLEAM_ATOMIC_PTR_INCLUDED
#define GLEAM_ATOMIC_PTR_INCLUDED

#include <glib.h>

namespace gleam {

template <class T>
class atomic_ptr
{
	typedef atomic_ptr<T>           this_type;

	/**
	 * Prevent copying and assignment
	 *
	 * This seems strange but I think it makes
	 * sense until I can think of a valid use 
	 * case for copying.
	 */
	atomic_ptr (const this_type&);
	this_type& operator= (const this_type&);

public:

	typedef T*                       pointer;

	atomic_ptr (pointer ptr = 0)
		:
			m_ptr(ptr)
	{ }

	pointer get () const
	{
		return g_atomic_pointer_get(&m_ptr);
	}

	void set (pointer new_ptr)
	{
		g_atomic_pointer_set (&m_ptr, new_ptr);
	}

	bool compare_and_exchange (pointer old_ptr, pointer new_ptr)
	{
		return g_atomic_pointer_compare_and_exchange
			(
			 &m_ptr,
			 old_ptr,
			 new_ptr
			);
	}

	/**
	 * convenience method, \see compare_and_exchange
	 */
	bool cas (pointer old_ptr, pointer new_ptr)
	{
		return compare_and_exchange (old_ptr, new_ptr);
	}

private:

	// Has to be mutable when using the apple version of gcc.
	mutable volatile pointer             m_ptr;

};

} // namespace gleam

#endif // GLEAM_ATOMIC_PTR_INCLUDED
