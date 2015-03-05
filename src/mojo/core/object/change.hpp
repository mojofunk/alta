#ifndef MOJO_CHANGE_H
#define MOJO_CHANGE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#include "mojo/core/object/property.hpp"
#endif

namespace mojo {

/**
 * A Change contains the information relating
 * to a state change in an Object class.
 */
class Change
{
private:

	Change ();

public:

	template <class ValueType>
	Change (const PropertyID& name_id, const ValueType& old_value)
		: old_value (name_id, old_value)
		, new_value ()
	{ }

	bool operator ! () const
	{
		return !old_value || !new_value;
	}

	bool operator< (const Change& other) const
	{
		return old_value.name < other.old_value.name;
	}

	template <class ValueType>
	bool
	set_new_value (const ValueType& new_value_arg)
	{
		new_value.name = old_value.name;
		new_value.value = new_value_arg;

		// The types must always be the same
		//assert (new_value.value.type() == old_value.value.type());
	}

	Property old_value;
	Property new_value;

};

} // namespace mojo

#endif // MOJO_CHANGE_H
