
#ifndef MOJO_AUDIO_FILE_MODULE
#define MOJO_AUDIO_FILE_MODULE

#include <vector>
#include <string>

#include <mojo/module.hpp>

#include <mojo/audio_file.hpp>
#include <mojo/audio_file_format.hpp>

namespace mojo {

class AudioFileModule : public Module
{
public: // typedefs

	typedef std::vector<AudioFileFormat*> Formats;

public: // constructors

	~AudioFileModule();

public: // interface

	/**
	 * return The audio file formats that are readable
	 * by the plugin
	 */
	virtual Formats get_readable_formats () const = 0;

	/**
	 * return The audio file formats that are writable
	 * by the plugin
	 */
	virtual Formats get_writable_formats () const = 0;

	/**
	 * return new AudioFile or 0 on failure
	 */
	virtual AudioFile * open (const std::string& path) = 0;

	/**
	 * return new AudioFile or 0 on failure
	 * open new audiofile for writing
	 */
	virtual AudioFile * open (const std::string& path,
			AudioFileFormat* format,
			samplerate_t rate,
			channel_count_t channels) = 0;

	/**
	 * There should be a close method
	 */

protected: // constructors

	AudioFileModule();

};

} // namespace mojo

#endif
