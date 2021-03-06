
#ifndef MOJO_CORE_H
#define MOJO_CORE_H

#include "config/common_header_includes.hpp"

//////

#include "macros/disallow_copy_and_assign.hpp"
#include "macros/private.hpp"
#include "macros/namespace.hpp"
#include "macros/smart_pointer_aliases.hpp"
#include "macros/declare_class_and_aliases.hpp"
#include "macros/strfunc.hpp"

MOJO_BEGIN_NAMESPACE

#include "misc/semaphore.hpp"
#include "misc/run_loop.hpp"

#include "threads/thread_name_registry.hpp"

#include "logging/fwd.hpp"
#include "logging/timestamp.hpp"
#include "logging/allocator.hpp"
#include "logging/string.hpp"
#include "logging/logging.hpp"
#include "logging/sink.hpp"
#include "logging/ostream_sink.hpp"
#include "logging/log.hpp"
#include "logging/logger.hpp"
#include "logging/format.hpp"
#include "logging/record.hpp"
#include "logging/async_log.hpp"
#include "logging/macros.hpp"

#include "audio/types.hpp"
#include "audio/timeline.hpp"
#include "audio/utils.hpp"
#include "audio/cycle_timer.hpp"

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

#include "time/chrono_timestamp.hpp"
#include "time/elapsed_timer.hpp"
#include "time/time.hpp"
#include "time/timing.hpp"

#include "memory/garbage_collector.hpp"
#include "memory/fixed_size_pool.hpp"
#include "memory/fixed_size_object_pool.hpp"
#include "memory/fixed_size_pool_allocator.hpp"
#include "memory/null_deleter.hpp"

#include "lockfree/ring_buffer.hpp"

#include "misc/functor_dispatcher.hpp"
#include "misc/sample_block.hpp"
#include "misc/spinwait.hpp"

#include "typesystem/forward.hpp"
#include "typesystem/typedefs.hpp"
#include "typesystem/type_names.hpp"
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
#include "system/cpu_id.hpp"

#include "string/compose.hpp"
#include "string/convert.hpp"
#include "string/string_pool.hpp"

#include "debug/debug_registry.hpp"
#include "debug/debug.hpp"
#include "debug/demangle.hpp"
#include "debug/stack_trace.hpp"

#include "object/forward.hpp"
#include "object/typedefs.hpp"
#include "object/object.hpp"
#include "object/object_collection.hpp"

#ifdef MOJO_WINDOWS
#include "native/windows_mmcss.hpp"
#include "native/windows_timer_utils.hpp"
#endif

MOJO_END_NAMESPACE

#endif // MOJO_CORE_H
