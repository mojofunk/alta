#ifndef MOJO_CORE_MACROS
#define MOJO_CORE_MACROS

#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#define MOJO_DEFINE_POINTER_TYPEDEFS(CLASS) \
	typedef boost::shared_ptr<CLASS>    CLASS##SPtr;\
	typedef boost::weak_ptr<CLASS>      CLASS##WPtr;

#define MOJO_DEFINE_POINTER_SET_TYPEDEFS(CLASS) \
	typedef std::set<CLASS##SPtr>         CLASS##Set;
#endif
