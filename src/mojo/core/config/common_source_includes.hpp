#ifndef MOJO_CORE_COMMON_SOURCE_H
#define MOJO_CORE_COMMON_SOURCE_H

/**
 * These are the common system/external includes required for source files
 * in mojo-core.
 */

#include "mojo/core/config/common_header_includes.hpp"

#include <cstring>
#include <cstdlib>
#include <iostream>

#ifdef MOJO_WINDOWS
#include <stdio.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif

#include <boost/tokenizer.hpp>

#endif
