#ifndef MOJO_SESSION_TYPES
#define MOJO_SESSION_TYPES

#include <inttypes.h>

namespace mojo {

enum Error {

};

enum TrackType {
	AUDIO,
	MIDI
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
