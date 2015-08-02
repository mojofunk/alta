#include "mojo-core.hpp"

#include "config/common_source_includes.hpp"

// Now include all source files

#include "audio/utils.cpp"

#include "midi/midi_util.cpp"

#include "debug/debug.cpp"

#include "filesystem/search_path.cpp"
#include "filesystem/filesystem_paths.cpp"
#include "filesystem/file_utils.cpp"

#include "init/initialize.cpp"

#include "time/time.cpp"
#include "time/timing.cpp"

#include "string/convert.cpp"

#include "misc/semaphore.cpp"
#include "misc/worker.cpp"
#include "misc/functor_dispatcher.cpp"
#include "misc/sample_block.cpp"

#include "logging/log.cpp"

#include "modules/glib_library.cpp"
#include "modules/library.cpp"
#include "modules/module.cpp"
#include "modules/module_utils.cpp"

#include "system/resource.cpp"
#include "system/utils.cpp"

#include "typesystem/type_names.cpp"
#include "typesystem/type_system.cpp"

#ifdef MOJO_WINDOWS
#include "native/windows_source_includes.hpp"
#include "native/windows_mmcss.cpp"
#include "native/windows_time_utils.cpp"
#endif
