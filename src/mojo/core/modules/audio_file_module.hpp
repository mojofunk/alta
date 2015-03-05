#ifndef MOJO_AUDIO_FILE_MODULE_H
#define MOJO_AUDIO_FILE_MODULE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#include "mojo/core/typesystem/types.hpp"
#include "mojo/core/modules/module.hpp"
#include "mojo/core/interfaces/typedefs.hpp"
#endif

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
	virtual AudioFileFormatSPSet get_readable_formats () const = 0;

	/**
	 * return The audio file formats that are writable
	 * by the plugin
	 */
	virtual AudioFileFormatSPSet get_writable_formats () const = 0;

	/**
	 * return new AudioFile or 0 on failure
	 */
	virtual AudioFileSP open (const std::string& path) = 0;

	/**
	 * return new AudioFile or 0 on failure
	 * open new audiofile for writing
	 */
	virtual AudioFileSP open (const std::string& path,
			AudioFileFormatSP format,
			samplerate_t rate,
			channel_count_t channels) = 0;

protected: // constructors

	AudioFileModule();

};

} // namespace mojo

#endif // MOJO_AUDIO_FILE_MODULE_H
