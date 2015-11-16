#ifndef MOJO_AUDIO_SEQUENCE_H
#define MOJO_AUDIO_SEQUENCE_H

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

#endif // MOJO_AUDIO_SEQUENCE_H
