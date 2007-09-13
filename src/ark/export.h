
#ifndef ARK_EXPORT_INCLUDED
#define ARK_EXPORT_INCLUDED

#ifdef _MSC_VER
	#define ARK_EXPORT __declspec(dllexport)
	#define ARK_IMPORT __declspec(dllimport)
	#define ARK_LOCAL
#else
	#define ARK_EXPORT __attribute__ ((visibility("default")))
	#define ARK_IMPORT __attribute__ ((visibility("default")))
	#define ARK_LOCAL __attribute__ ((visibility("hidden")))
#endif

#ifdef BUILDING_DLL
	#define ARK_API ARK_EXPORT
#else
	#define ARK_API ARK_IMPORT
#endif

#define ARK_CAPI extern "C" ARK_API

#endif
