#ifndef GLEAM_ATOMIC_COUNTER_INCLUDED
#define GLEAM_ATOMIC_COUNTER_INCLUDED

#include <glib.h>

namespace gleam {

class atomic_counter
{
	/**
	 * Prevent copying and assignment
	 *
	 * This seems strange but I think it makes
	 * sense until I can think of a valid use 
	 * case for copying.
	 */
	atomic_counter (const atomic_counter&);
	atomic_counter& operator= (const atomic_counter&);

public:

	atomic_counter (gint value = 0)
		:
			m_value(value)
	{ }

	gint get() const
	{
		return g_atomic_int_get (&m_value);
	}

	void set (gint new_value)
	{
		g_atomic_int_set (&m_value, new_value);
	}

	void increment ()
	{
		g_atomic_int_inc (&m_value);
	}

	void operator++ ()
	{
		increment ();
	}

	bool decrement_and_test ()
	{
		return g_atomic_int_dec_and_test (&m_value);
	}
	
	bool operator-- ()
	{
		return decrement_and_test ();
	}

	bool compare_and_exchange (gint old_value, gint new_value)
	{
		return g_atomic_int_compare_and_exchange
			(
			 &m_value,
			 old_value,
			 new_value
			);
	}

	/**
	 * convenience method, \see compare_and_exchange
	 */
	bool cas (gint old_value, gint new_value)
	{
		return compare_and_exchange (old_value, new_value);
	}

private:

	// Has to be mutable when using the apple version of gcc.
	mutable gint                   m_value;

};

} // namespace gleam

#endif // GLEAM_ATOMIC_COUNTER_INCLUDED
