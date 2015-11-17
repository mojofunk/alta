#ifndef MOJO_MOJO_AUDIO_EFFECT_H
#define MOJO_MOJO_AUDIO_EFFECT_H

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

#include <mojo/audio_effect/forward.hpp>
#include <mojo/audio_effect/typedefs.hpp>
#include <mojo/audio_effect/audio_effect.hpp>
#include <mojo/audio_effect/audio_effect_info.hpp>
#include <mojo/audio_effect/audio_effect_parameter_info.hpp>
#include <mojo/audio_effect/audio_effect_module.hpp>

MOJO_END_NAMESPACE

#endif // MOJO_MOJO_AUDIO_EFFECT_H
