#ifndef MOJO_VISIBILITY_H
#define MOJO_VISIBILITY_H

#ifdef _MSC_VER
	#define MOJO_EXPORT __declspec(dllexport)
	#define MOJO_IMPORT __declspec(dllimport)
	#define MOJO_LOCAL
#else
	#define MOJO_EXPORT __attribute__ ((visibility("default")))
	#define MOJO_IMPORT __attribute__ ((visibility("default")))
	#define MOJO_LOCAL __attribute__ ((visibility("hidden")))
#endif

#ifdef MOJO_BUILD_STATIC

	#define MOJO_API
	#define MOJO_LOCAL

#else // building shared

#ifdef MOJO_BUILDING_DLL
	#define MOJO_API MOJO_EXPORT
#else
	#define MOJO_API MOJO_IMPORT
#endif

#endif

#define MOJO_CAPI extern "C" MOJO_API

#endif // MOJO_VISIBILITY_H
