#ifndef MOJO_CORE_COMMON_HEADER_H
#define MOJO_CORE_COMMON_HEADER_H

/**
 * This is the common header file that is included by
 * each header file.
 */

#include "target_platform.hpp"
#include "compiler_defines.hpp"
#include "visibility.hpp"
#include "version.hpp"

/**
 * These are the common system includes required by header files
 * in mojo-core. Obviously not all header files require all these
 * includes.
 */

#include <string>
#include <map>
#include <vector>

#include <boost/filesystem.hpp>

#endif // MOJO_CORE_COMMON_HEADER_H
