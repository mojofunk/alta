
#ifndef MOJO_SNDFILE_AUDIO_FILE_MODULE
#define MOJO_SNDFILE_AUDIO_FILE_MODULE

#include "mojo/interfaces/audio_file_module.hpp"

namespace mojo {

class SndfileAudioFileModule : public AudioFileModule
{
public: // constructors

	SndfileAudioFileModule();
	~SndfileAudioFileModule();

public: // Module interface

	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // AudioFileModule interface
	
	virtual AudioFileFormatSPSet get_readable_formats () const;

	virtual AudioFileFormatSPSet get_writable_formats () const;
	
	virtual AudioFileSP open(const std::string& path);

	virtual AudioFileSP open(const std::string& path,
			AudioFileFormatSP format,
			samplerate_t rate,
			channel_count_t channels);

private: // member data

	AudioFileFormatSPSet m_readable_formats;

	AudioFileFormatSPSet m_writable_formats;

private: // member functions

	static void get_readable_formats (AudioFileFormatSPSet&);

	static void get_writable_formats (AudioFileFormatSPSet&);

};

} // namespace mojo

#endif
