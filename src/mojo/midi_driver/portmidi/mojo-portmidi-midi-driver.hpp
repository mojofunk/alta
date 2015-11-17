#ifndef MOJO_MOJO_PORTMIDI_MIDI_DRIVER_H
#define MOJO_MOJO_PORTMIDI_MIDI_DRIVER_H

/**
 * These include paths need to be identical to what they would be
 * as if the headers were installed in a system wide location.
 *
 * For instance if install path was /usr/include/mojo-1.0/
 *
 * Users of mojo would include top level headers such as mojo-core.hpp
 * which include headers from subdirectories which need to prefixed
 * with the library name in the unlikely event of a header path clash.
 */

#include <mojo-midi-driver.hpp>

#include <portmidi.h>
#include <pmutil.h>
#include <porttime.h>

MOJO_BEGIN_NAMESPACE

#include <mojo/midi_driver/portmidi/portmidi_midi_input_device.hpp>
#include <mojo/midi_driver/portmidi/portmidi_midi_output_device.hpp>
#include <mojo/midi_driver/portmidi/portmidi_midi_driver.hpp>
#include <mojo/midi_driver/portmidi/portmidi_midi_driver_module.hpp>

MOJO_END_NAMESPACE

#endif // MOJO_MOJO_PORTMIDI_MIDI_DRIVER_H
