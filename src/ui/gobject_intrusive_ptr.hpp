
#ifndef GOBJECT_INTRUSIVE_PTR_INCLUDED
#define GOBJECT_INTRUSIVE_PTR_INCLUDED

#include <glib-object.h>

namespace boost {

template <class T>
void
intrusive_ptr_add_ref(T* gobj)
{
	g_object_ref(gobj);
}

template <class T>
void
intrusive_ptr_release(T* gobj)
{
	g_object_unref(gobj);
}

}

#endif
