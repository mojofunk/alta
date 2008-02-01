
#ifndef MOJO_SNDFILE_AUDIO_FILE_PLUGIN_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_PLUGIN_INCLUDED

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

	virtual Formats get_writable_formats () const;
	
	virtual AudioFile * open(const std::string& path);

	virtual AudioFile * open(const std::string& path,
			AudioFileFormat* format,
			samplerate_t rate,
			channel_count_t channels);

private: // member data

	Formats m_readable_formats;

	Formats m_writable_formats;

private: // member functions

	static void get_readable_formats (Formats&);

	static void get_writable_formats (Formats&);

	static void delete_formats (Formats&);

};

} // namespace mojo

#endif
