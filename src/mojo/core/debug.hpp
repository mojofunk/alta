#ifndef MOJO_CORE_DEBUG
#define MOJO_CORE_DEBUG

#include <iostream>

#include <glib.h>

#define LOG \
	std::cerr << G_STRFUNC << " " << std::endl;

#endif
