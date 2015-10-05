
#ifndef MOJO_CORE_H
#define MOJO_CORE_H

#include "config/common_header_includes.hpp"

//////

#include "audio/types.hpp"
#include "audio/utils.hpp"

#include "midi/midi_util.hpp"

#include "init/initialize.hpp"

#include "object/signals.hpp"
#include "object/property.hpp"
#include "object/properties.hpp"
#include "object/change.hpp"
#include "object/change_set.hpp"

#include "filesystem/filesystem.hpp"
#include "filesystem/search_path.hpp"
#include "filesystem/filesystem_paths.hpp"
#include "filesystem/file_utils.hpp"

#include "time/time.hpp"
#include "time/timing.hpp"

#include "memory/fixed_size_pool.hpp"
#include "memory/fixed_size_object_pool.hpp"
#include "memory/fixed_size_pool_allocator.hpp"

#include "misc/ring_buffer.hpp"
#include "misc/null_deleter.hpp"
#include "misc/semaphore.hpp"
#include "misc/worker.hpp"
#include "misc/functor_dispatcher.hpp"
#include "misc/sample_block.hpp"
#include "misc/spinwait.hpp"

#include "logging/log.hpp"

#include "typesystem/smart_pointer_macros.hpp"
#include "typesystem/type_names.hpp"
#include "typesystem/forward.hpp"
#include "typesystem/typedefs.hpp"
#include "typesystem/type_factory.hpp"
#include "typesystem/template_type_factory.hpp"
#include "typesystem/type_registry.hpp"
#include "typesystem/type_system.hpp"

#include "modules/forward.hpp"
#include "modules/typedefs.hpp"
#include "modules/module.hpp"
#include "modules/module_utils.hpp"
#include "modules/library.hpp"
#include "modules/glib_library.hpp"

#include "system/resource.hpp"
#include "system/utils.hpp"

#include "string/compose.hpp"
#include "string/convert.hpp"

#include "debug/debug_registry.hpp"
#include "debug/debug.hpp"

#include "object/forward.hpp"
#include "object/typedefs.hpp"
#include "object/object.hpp"
#include "object/object_collection.hpp"

#ifdef MOJO_WINDOWS
#include "native/windows_mmcss.hpp"
#include "native/windows_time_utils.hpp"
#endif

#endif // MOJO_CORE_H
