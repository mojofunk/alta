
#ifndef MOJO_CORE_H
#define MOJO_CORE_H

#include "visibility.hpp"

//////

#include "object/signals.hpp"
#include "object/property.hpp"
#include "object/properties.hpp"
#include "object/change.hpp"
#include "object/change_set.hpp"

#include "filesystem/filesystem.hpp"
#include "filesystem/filesystem_paths.hpp"
#include "filesystem/file_utils.hpp"
#include "filesystem/search_path.hpp"

#include "time/time.hpp"
#include "time/timing.hpp"

#include "misc/null_deleter.hpp"
#include "misc/functor_dispatcher.hpp"
#include "misc/worker.hpp"
#include "misc/sample_block.hpp"
#include "misc/spinwait.hpp"

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

#include "system/resource.hpp"

#include "semaphore.hpp"

#include "string/compose.hpp"
#include "string/convert.hpp"

#include "debug/debug_registry.hpp"
#include "debug/debug.hpp"

#include "typesystem/types.hpp"
#include "typesystem/type_names.hpp"
#include "typesystem/forward.hpp"
#include "typesystem/template_type_factory.hpp"
#include "typesystem/typedefs.hpp"
#include "typesystem/type_factory.hpp"
#include "typesystem/type_system.hpp"

#include "object/forward.hpp"
#include "object/typedefs.hpp"
#include "object/object.hpp"
#include "object/object_collection.hpp"

#endif // MOJO_CORE_H
