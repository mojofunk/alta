#ifndef MOJO_LOGGING_DEBUG_H
#define MOJO_LOGGING_DEBUG_H

#ifdef LOGGING_ENABLE_DEBUG_OUTPUT
#define LOGGING_DEBUG(...) printf(__VA_ARGS__)
#else
#define LOGGING_DEBUG(...)
#endif

#endif // MOJO_LOGGING_DEBUG_H
