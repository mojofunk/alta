#ifndef MOJO_AUDIO_SEQUENCE
#define MOJO_AUDIO_SEQUENCE

#include "mojo/core/object.hpp"

#include "typedefs.hpp"

#include <set>

namespace mojo {

class AudioSequence : public Object
{
public:

	typedef std::set<AudioEventSP>       container_t;
	typedef container_t::iterator          iterator;
	typedef container_t::const_iterator    const_iterator;
	typedef container_t::size_type         size_type;

public:

	AudioSequence();

public:
	
	// Object interface

	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public:

	// methods
	std::pair<iterator, bool> insert (AudioEventSP ae);

	size_type erase (AudioEventSP ae);

private:

	// member data
	container_t m_audio_events;

private:

	static const char* const s_property_audio_events;

};

} // namespace mojo

#endif
