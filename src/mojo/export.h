
#ifndef MOJO_EXPORT_INCLUDED
#define MOJO_EXPORT_INCLUDED

#ifdef _MSC_VER
	#define MOJO_EXPORT __declspec(dllexport)
	#define MOJO_IMPORT __declspec(dllimport)
	#define MOJO_LOCAL
#else
	#define MOJO_EXPORT __attribute__ ((visibility("default")))
	#define MOJO_IMPORT __attribute__ ((visibility("default")))
	#define MOJO_LOCAL __attribute__ ((visibility("hidden")))
#endif

#ifdef BUILDING_DLL
	#define MOJO_API MOJO_EXPORT
#else
	#define MOJO_API MOJO_IMPORT
#endif

#define MOJO_CAPI extern "C" MOJO_API

#endif
