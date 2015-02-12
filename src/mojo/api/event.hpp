#ifndef MOJO_EVENT_H
#define MOJO_EVENT_H

#include "mojo/core/types.hpp"

#include "object.hpp"

namespace mojo {

class Event : public Object
{
public:

	Event();

	Event(const count_t& pos, const count_t& dur);

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);


public:

	/*
	virtual void set_position (const count_t& new_pos) = 0;

	virtual void get_position (count_t& pos) = 0;

	void set_duration (const count_t& new_pos) = 0;

	void get_duration (count_t& pos) = 0;
	*/

protected:

	count_t		position;
	count_t		duration;

private:

	// property ID's
	static PropertyID const s_property_position_id;
	static PropertyID const s_property_duration_id;

};

} // namespace mojo

#endif // MOJO_EVENT_H
