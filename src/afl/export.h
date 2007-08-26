
#ifndef AFL_EXPORT_INCLUDED
#define AFL_EXPORT_INCLUDED

#ifdef _MSC_VER
	#define AFL_EXPORT __declspec(dllexport)
	#define AFL_IMPORT __declspec(dllimport)
	#define AFL_LOCAL
#else
	#define AFL_EXPORT __attribute__ ((visibility("default")))
	#define AFL_IMPORT __attribute__ ((visibility("default")))
	#define AFL_LOCAL __attribute__ ((visibility("hidden")))
#endif

#ifdef BUILDING_DLL
	#define AFL_API AFL_EXPORT
#else
	#define AFL_API AFL_IMPORT
#endif

#endif
