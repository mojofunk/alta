#ifndef MOJO_MIDI_DRIVER_TYPEDEFS_H
#define MOJO_MIDI_DRIVER_TYPEDEFS_H

#include <mojo/core/config/common_header_includes.hpp>
#include <mojo/core/typesystem/smart_pointer_macros.hpp>
#include <mojo/midi_driver/forward.hpp>

namespace mojo {

MOJO_DEFINE_ALL_TYPEDEFS(MIDIDevice)
MOJO_DEFINE_ALL_TYPEDEFS(MIDIInputDevice)
MOJO_DEFINE_ALL_TYPEDEFS(MIDIOutputDevice)
MOJO_DEFINE_ALL_TYPEDEFS(MIDIDriver)
MOJO_DEFINE_ALL_TYPEDEFS(MIDIDriverModule)

} // namespace mojo

#endif // MOJO_MIDI_DRIVER_TYPEDEFS_H
