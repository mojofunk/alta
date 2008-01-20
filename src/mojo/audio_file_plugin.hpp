
#ifndef MOJO_AUDIO_FILE_PLUGIN_INCLUDED
#define MOJO_AUDIO_FILE_PLUGIN_INCLUDED

#include <vector>
#include <string>

#include <mojo/plugin.hpp>

#include <mojo/audio_file.hpp>
#include <mojo/audio_file_format.hpp>

namespace mojo {

class AudioFilePlugin : public Plugin
{
public: // typedefs

	typedef std::vector<AudioFileFormat*> Formats;

public: // constructors

	~AudioFilePlugin();

public: // interface

	virtual Formats get_readable_formats () const = 0;

	/**
	 * return new AudioFile or 0 on failure
	 */
	virtual AudioFile * open (const std::string& path) = 0;

protected: // constructors

	AudioFilePlugin();

};

} // namespace mojo

#endif
