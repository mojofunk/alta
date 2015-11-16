#ifndef MOJO_CORE_LOGGING_H
#define MOJO_CORE_LOGGING_H

namespace mojo {

MOJO_API void* log_malloc(std::size_t size);

MOJO_API void log_free(void* ptr);

MOJO_API void log_initialize();

MOJO_API void log_deinitialize();

} // namespace mojo

#endif // MOJO_CORE_LOGGING_H
