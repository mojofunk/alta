
#ifndef MOJO_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED

#include <mojo/audio_file_plugin.hpp>

namespace mojo {

class SndfileAudioFilePlugin : public AudioFilePlugin
{
public: // constructors

	SndfileAudioFilePlugin();
	~SndfileAudioFilePlugin();

public: // Plugin interface

	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // AudioFilePlugin interface
	
	virtual Formats get_readable_formats () const;
	
	virtual AudioFile * open(const std::string& path);

private: // member data

	Formats m_readable_formats;

};

}

#endif
