
#ifndef MOJO_SNDFILE_AUDIO_FILE_MODULE
#define MOJO_SNDFILE_AUDIO_FILE_MODULE

#include <mojo/mojo.hpp>

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
	
	virtual AudioFileFormatSet get_readable_formats () const;

	virtual AudioFileFormatSet get_writable_formats () const;
	
	virtual AudioFileSPtr open(const std::string& path);

	virtual AudioFileSPtr open(const std::string& path,
			AudioFileFormatSPtr format,
			samplerate_t rate,
			channel_count_t channels);

private: // member data

	AudioFileFormatSet m_readable_formats;

	AudioFileFormatSet m_writable_formats;

private: // member functions

	static void get_readable_formats (AudioFileFormatSet&);

	static void get_writable_formats (AudioFileFormatSet&);

};

} // namespace mojo

#endif
