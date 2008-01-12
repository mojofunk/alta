#ifndef MOJO_AUDIO_SEQUENCE_INCLUDED
#define MOJO_AUDIO_SEQUENCE_INCLUDED

#include <mojo/object.hpp>
#include <mojo/audio_event_ptr.hpp>

#include <set>

namespace mojo {

class AudioSequence : public Object
{
public:

	typedef std::set<AudioEventSPtr>       container_t;
	typedef container_t::iterator          iterator;
	typedef container_t::const_iterator    const_iterator;
	typedef container_t::size_type         size_type;

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
	std::pair<iterator, bool> insert (AudioEventSPtr ae);

	size_type erase (AudioEventSPtr ae);

private:

	// member data
	container_t m_audio_events;

private:

	static const char* const s_property_audio_events;

};

}

#endif
