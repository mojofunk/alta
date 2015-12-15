#include "mojo-core.hpp"

#include "config/common_source_includes.hpp"

MOJO_BEGIN_NAMESPACE

// Now include all source files

#include "logging/debug.hpp"
#include "logging/allocator.cpp"
#include "logging/format.cpp"
#include "logging/record.cpp"
#include "logging/log.cpp"
#include "logging/logger.cpp"
#include "logging/async_log.cpp"
#include "logging/ostream_sink.cpp"
#include "logging/logging.cpp"

#include "audio/utils.cpp"

#include "midi/midi_util.cpp"

#include "debug/debug.cpp"
#include "debug/demangle.cpp"
#include "debug/stack_trace.cpp"

#include "filesystem/search_path.cpp"
#include "filesystem/filesystem_paths.cpp"
#include "filesystem/file_utils.cpp"

#include "init/initialize.cpp"

#include "time/time.cpp"
#include "time/timing.cpp"

#include "string/convert.cpp"

#include "memory/garbage_collector.cpp"

#include "misc/semaphore.cpp"
#include "misc/run_loop.cpp"
#include "misc/functor_dispatcher.cpp"
#include "misc/sample_block.cpp"

#include "modules/module.cpp"
#include "modules/module_utils.cpp"
#include "modules/library.cpp"
#include "modules/glib_library.cpp"

#include "system/resource.cpp"
#include "system/utils.cpp"

#include "typesystem/type_names.cpp"
#include "typesystem/type_system.cpp"

#ifdef MOJO_WINDOWS
#include "native/windows_source_includes.hpp"
#include "native/windows_mmcss.cpp"
#include "native/windows_timer_utils.cpp"
#endif

MOJO_END_NAMESPACE
