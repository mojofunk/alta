#ifndef MOJO_MOJO_AUDIO_DRIVER_H
#define MOJO_MOJO_AUDIO_DRIVER_H

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

#include <mojo/audio_driver/forward.hpp>

#include <mojo/audio_driver/typedefs.hpp>

#include <mojo/audio_driver/audio_device.hpp>
#include <mojo/audio_driver/audio_driver_module.hpp>

#endif // MOJO_MOJO_AUDIO_DRIVER_H
