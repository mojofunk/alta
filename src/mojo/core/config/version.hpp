#ifndef MOJO_CORE_VERSION_H
#define MOJO_CORE_VERSION_H

/**
 * These are somewhat arbitrary at this point with no strict
 * adherence to standard industry practice but intent is to follow
 * semver.org guidelines.
 */

#define MOJO_MAJOR_VERSION 0
#define MOJO_MINOR_VERSION 1
#define MOJO_MICRO_VERSION 1

#define MOJO_VERSION ((MOJO_MAJOR_VERSION << 16) + (MOJO_MINOR_VERSION << 8) + MOJO_MICRO_VERSION)

#endif // MOJO_CORE_VERSION_H
