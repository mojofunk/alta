#ifndef MOJO_MOJO_AUDIO_FILE_H
#define MOJO_MOJO_AUDIO_FILE_H

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

MOJO_BEGIN_NAMESPACE

#include <mojo/audio_file/forward.hpp>
#include <mojo/audio_file/typedefs.hpp>
#include <mojo/audio_file/audio_file.hpp>
#include <mojo/audio_file/audio_file_format.hpp>
#include <mojo/audio_file/audio_file_module.hpp>

MOJO_END_NAMESPACE

#endif // MOJO_MOJO_AUDIO_FILE_H
