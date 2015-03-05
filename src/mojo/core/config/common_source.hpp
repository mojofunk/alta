#ifndef MOJO_CORE_COMMON_SOURCE_H
#define MOJO_CORE_COMMON_SOURCE_H

/**
 * These are the common system/external includes required for source files
 * in mojo-core.
 *
 * The only other headers included by source files should be internal
 * headers and then only when MOJO_CORE_AMALGAMATED is not defined.
 */

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

#include <gmodule.h>

#include <gleam/filesystem_paths.hpp>
#include <gleam/utils.hpp>

#include <boost/tokenizer.hpp>

#endif
