
#ifndef MOJO_CORE_H
#define MOJO_CORE_H

#include "visibility.hpp"

//////

#include "property.hpp"
#include "properties.hpp"

#include "change.hpp"
#include "change_set.hpp"

#include "filesystem/filesystem.hpp"
#include "filesystem/filesystem_paths.hpp"
#include "filesystem/file_utils.hpp"
#include "filesystem/search_path.hpp"

#include "functor_dispatcher.hpp"

#include "logging/log.hpp"

#include "smart_pointer_macros.hpp"

#include "interfaces/forward.hpp"
#include "interfaces/typedefs.hpp"

#include "modules/forward.hpp"
#include "modules/typedefs.hpp"
#include "modules/module.hpp"
#include "modules/module_utils.hpp"
#include "modules/library.hpp"
#include "modules/glib_library.hpp"

#include "modules/archive_module.hpp"
#include "modules/audio_driver_module.hpp"
#include "modules/audio_effect_module.hpp"
#include "modules/audio_file_module.hpp"
#include "modules/project_export_module.hpp"
#include "modules/project_import_module.hpp"

#include "null_deleter.hpp"

#include "resource.hpp"

#include "sample_block.hpp"

#include "semaphore.hpp"

#include "signals.hpp"

#include "string/compose.hpp"
#include "string/convert.hpp"

#include "debug/debug_registry.hpp"
#include "debug/debug.hpp"

#include "time/time.hpp"
#include "time/timing.hpp"

#include "spinwait.hpp"

#include "type_names.hpp"

#include "types.hpp"

#include "typesystem/forward.hpp"
#include "typesystem/template_type_factory.hpp"
#include "typesystem/typedefs.hpp"
#include "typesystem/type_factory.hpp"
#include "typesystem/type_system.hpp"

#include "worker.hpp"

#endif // MOJO_CORE_H
