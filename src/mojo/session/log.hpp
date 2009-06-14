#ifndef SESSION_LOG
#define SESSION_LOG

#include <iostream>

#include <glib.h>

#define LOG \
	std::cerr << G_STRFUNC << " " << std::endl;

#endif
