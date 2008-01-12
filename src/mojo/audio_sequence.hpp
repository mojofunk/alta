#ifndef MOJO_AUDIO_SEQUENCE_INCLUDED
#define MOJO_AUDIO_SEQUENCE_INCLUDED

#include <mojo/object.hpp>
#include <mojo/audio_event_ptr.hpp>

#include <set>

namespace mojo {

class AudioSequence : public Object
{
public:

	AudioSequence();

public:
	
	// Object interface
	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual std::vector<std::string> get_property_names () const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

public:

	// methods
	bool add (AudioEventSPtr ae);

	void remove (AudioEventSPtr ae);

private:

	// member data
	std::set<AudioEventSPtr> m_audio_events;

private:

	static const std::string property_audio_events;

};

}

#endif
