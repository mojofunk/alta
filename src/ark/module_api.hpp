
#ifndef ARK_MODULE_API_INCLUDED
#define ARK_MODULE_API_INCLUDED

#include <ark/module_info.hpp>
#include <ark/archive_reader.hpp>
#include <ark/archive_writer.hpp>

namespace ark {

using std::string;

typedef ModuleInfo (*module_info_func_t) ();

typedef ArchiveReader* (*reader_factory_func_t) (const ArchiveFormat& format);

typedef ArchiveWriter* (*writer_factory_func_t) (const ArchiveFormat& format);

} // namespace ark

#endif
