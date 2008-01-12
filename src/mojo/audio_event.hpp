#ifndef MOJO_AUDIO_EVENT_INCLUDED
#define MOJO_AUDIO_EVENT_INCLUDED

#include <mojo/event.hpp>

namespace mojo {

class AudioEvent : public Event
{
public:

	// Object interface
	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual std::vector<std::string> get_property_names () const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

public:


};

}

#endif
