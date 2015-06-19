#ifndef MOJO_AUDIO_SEQUENCE_H
#define MOJO_AUDIO_SEQUENCE_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/object/object.hpp"

#include "typedefs.hpp"
#endif

namespace mojo {

class AudioSequence : public Object {
public: // typedefs
	typedef AudioEventSPSet::iterator iterator;
	typedef AudioEventSPSet::const_iterator const_iterator;
	typedef AudioEventSPSet::size_type size_type;

public:
	AudioSequence();

public: // Object interface
	virtual void get_properties(Properties& props) const;

	virtual void set_properties(const Properties& props);

public: // methods
	std::pair<iterator, bool> insert(AudioEventSP ae);

	size_type erase(AudioEventSP ae);

private: // member data
	AudioEventSPSet m_audio_events;

private:
	static const char* const s_property_audio_events;
};

} // namespace mojo

#endif // MOJO_AUDIO_SEQUENCE_H
