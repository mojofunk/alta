#ifndef MOJO_CORE_CONFIG_TARGET_PLATFORM_H
#define MOJO_CORE_CONFIG_TARGET_PLATFORM_H

#if defined(_WIN32)
#define MOJO_WINDOWS
#elif defined(__linux__)
#define MOJO_LINUX
#else
#warning "Unsupported target platform"
#endif

// mac?
// non-linux/posix?
// android?

#endif
