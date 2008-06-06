#ifndef UI_LOG
#define UI_LOG

#include <iostream>

#include <glib.h>

#define LOG \
	std::cerr << G_STRFUNC << " " << std::endl;

#endif
