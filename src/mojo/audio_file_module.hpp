
#ifndef MOJO_AUDIO_FILE_MODULE
#define MOJO_AUDIO_FILE_MODULE

#include <string>

#include <mojo/core/types.hpp>

#include <mojo/module.hpp>
#include <mojo/typedefs.hpp>

namespace mojo {

class AudioFileModule : public Module
{
public: // constructors

	~AudioFileModule();

public: // interface

	/**
	 * return The audio file formats that are readable
	 * by the plugin
	 */
	virtual AudioFileFormatSet get_readable_formats () const = 0;

	/**
	 * return The audio file formats that are writable
	 * by the plugin
	 */
	virtual AudioFileFormatSet get_writable_formats () const = 0;

	/**
	 * return new AudioFile or 0 on failure
	 */
	virtual AudioFileSPtr open (const std::string& path) = 0;

	/**
	 * return new AudioFile or 0 on failure
	 * open new audiofile for writing
	 */
	virtual AudioFileSPtr open (const std::string& path,
			AudioFileFormatSPtr format,
			samplerate_t rate,
			channel_count_t channels) = 0;

protected: // constructors

	AudioFileModule();

};

} // namespace mojo

#endif
