#ifndef MOJO_CORE_COMMON_HEADER_H
#define MOJO_CORE_COMMON_HEADER_H

/**
 * This is the common header file that is included by
 * each header file.
 */

#include "mojo/core/config/target_platform.hpp"
#include "mojo/core/config/compiler_defines.hpp"
#include "mojo/core/config/visibility.hpp"
#include "mojo/core/config/version.hpp"

/**
 * These are the common system includes required by header files in mojo-core.
 * Not all header files require all these includes but they can rely on them
 * being already included.
 */

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <cstdint>
#include <string>
#include <sstream>
#include <typeinfo> // could possibly forward declare?
#include <limits>
#include <locale>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <queue>

#include <glib.h> // for Properties

#include <boost/any.hpp>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp>

#include "cppformat/format.h"

#endif // MOJO_CORE_COMMON_HEADER_H
