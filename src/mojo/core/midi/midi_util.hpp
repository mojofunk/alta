#ifndef MOJO_CORE_MIDI_UTIL_H
#define MOJO_CORE_MIDI_UTIL_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

struct MidiEventHeader {
	uint64_t time;
	size_t size;
	MidiEventHeader(const uint64_t t, const size_t s)
	    : time(t)
	    , size(s)
	{
	}
};

// rename to get_midi_message_size?
// @return -1 to indicate error
int get_midi_msg_length(uint8_t status_byte);

} // namespace mojo

#endif // MOJO_CORE_MIDI_UTIL_H
