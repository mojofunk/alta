#ifndef MOJO_STRFUNC_H
#define MOJO_STRFUNC_H

#if defined(__GNUC__)
#define MOJO_STRFUNC ((const char*)(__PRETTY_FUNCTION__))
#elif defined(_MSC_VER)
#define MOJO_STRFUNC ((const char*)(__FUNCSIG__))
#else
#define MOJO_STRFUNC ((const char*)(__func__))
#endif

#endif // MOJO_STRFUNC_H
