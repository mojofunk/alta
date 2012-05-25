#ifndef MOJO_APPLICATION_TYPES
#define MOJO_APPLICATION_TYPES

#include "mojo/core/types.hpp"

namespace mojo {

enum Error {

};

enum TrackType {
	AUDIO,
	MIDI
};

struct ImportOptions
{
	bool copy_files;
	bool convert_samplerate;
	bool convert_samplesize;
	bool split_channels;
};

struct TrackOptions
{
	TrackType type;
	uint8_t count;

	TrackOptions () : type(AUDIO), count(1) { }

	TrackOptions (const TrackOptions& other)
		: type(other.type)
		  , count(other.count) { }
};

} // namespace mojo

#endif
