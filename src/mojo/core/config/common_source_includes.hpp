#ifndef MOJO_CORE_COMMON_SOURCE_H
#define MOJO_CORE_COMMON_SOURCE_H

/**
 * These are the common system/external includes required for source files
 * in mojo-core.
 *
 * The only other headers included by source files should be internal
 * headers and then only when MOJO_CORE_AMALGAMATED is not defined.
 */

#include "mojo/core/config/common_header_includes.hpp"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <chrono>

#ifdef MOJO_WINDOWS
#include <stdio.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif

#include <gmodule.h>

#include <gleam/filesystem_paths.hpp>
#include <gleam/utils.hpp>

#include <boost/tokenizer.hpp>

#endif
