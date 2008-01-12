#ifndef MOJO_EVENT_INCLUDED
#define MOJO_EVENT_INCLUDED

#include <mojo/types.hpp>
#include <mojo/object.hpp>

namespace mojo {

class Event : public Object
{
public:

	// Object interface
	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual std::vector<std::string> get_property_names () const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

public:

	count_t		position;
	count_t		duration;

private:

	// property names
	static const char * const s_property_position;
	static const char * const s_property_duration;

};

}

#endif
