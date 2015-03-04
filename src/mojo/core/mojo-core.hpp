
#ifndef MOJO_CORE_H
#define MOJO_CORE_H

#include "visibility.hpp"

//////

#include "change.hpp"
#include "change_set.hpp"

#include "filesystem/filesystem.hpp"
#include "filesystem/filesystem_paths.hpp"
#include "filesystem/file_utils.hpp"
#include "filesystem/search_path.hpp"

#include "functor_dispatcher.hpp"

#include "log.hpp"

#include "smart_pointer_macros.hpp"

#include "modules/forward.hpp"
#include "modules/typedefs.hpp"
#include "modules/module.hpp"
#include "modules/module_utils.hpp"
#include "modules/library.hpp"
#include "modules/glib_library.hpp"

#include "null_deleter.hpp"

#include "property.hpp"
#include "properties.hpp"

#include "resource.hpp"

#include "sample_block.hpp"

#include "semaphore.hpp"

#include "signals.hpp"

#include "string/compose.hpp"
#include "string/convert.hpp"

#include "debug_registry.hpp"
#include "debug.hpp"

#include "time.hpp"
#include "timing.hpp"

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
