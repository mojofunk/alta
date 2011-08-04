#ifndef MOJO_TYPESYSTEM_MACROS
#define MOJO_TYPESYSTEM_MACROS

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#define MOJO_DEFINE_POINTER_TYPEDEFS(CLASS) \
	typedef boost::shared_ptr<CLASS>    CLASS##SP;\
	typedef boost::weak_ptr<CLASS>      CLASS##WP;\
	typedef boost::shared_ptr<CLASS const>    CLASS##ConstSP;\
	typedef boost::weak_ptr<CLASS const>      CLASS##ConstWP;

#endif
