#ifndef MOJO_MOJO_APPLICATION_H
#define MOJO_MOJO_APPLICATION_H

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
#include <mojo-core.hpp>

#include <mojo-archive.hpp>
#include <mojo-audio-driver.hpp>
#include <mojo-audio-effect.hpp>
#include <mojo-audio-file.hpp>
#include <mojo-midi-driver.hpp>

#include <mojo/application/types.hpp>

#include <mojo/application/forward.hpp>

#include <mojo/application/typedefs.hpp>

#include <mojo/application/utils.hpp>

#include <mojo/application/event.hpp>
#include <mojo/application/audio_clip.hpp>
#include <mojo/application/audio_event.hpp>
#include <mojo/application/audio_region_event.hpp>
#include <mojo/application/audio_region.hpp>
#include <mojo/application/audio_sequence.hpp>
#include <mojo/application/track.hpp>
#include <mojo/application/audio_track.hpp>
#include <mojo/application/directory_names.hpp>
#include <mojo/application/midi_track.hpp>
#include <mojo/application/project_directory.hpp>
#include <mojo/application/project.hpp>
#include <mojo/application/state_tracker.hpp>
#include <mojo/application/transition.hpp>
#include <mojo/application/transport.hpp>

#include <mojo/application/application_data.hpp>

#include <mojo/application/application.hpp>

#endif // MOJO_MOJO_APPLICATION_H
