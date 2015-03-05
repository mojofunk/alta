#ifndef MOJO_CORE_SMART_POINTER_MACROS_H
#define MOJO_CORE_SMART_POINTER_MACROS_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#endif

#define MOJO_DEFINE_POINTER_TYPEDEFS(CLASS) \
	using CLASS##SP = boost::shared_ptr<CLASS>;\
	using CLASS##WP = boost::weak_ptr<CLASS>;\
	using CLASS##ConstSP = boost::shared_ptr<CLASS const>;\
	using CLASS##ConstWP = boost::weak_ptr<CLASS const>;

#define MOJO_DEFINE_POINTER_SET_TYPEDEFS(CLASS) \
	using CLASS##SPSet = std::set<CLASS##SP>;\
	using CLASS##WPSet = std::set<CLASS##WP>;

#define MOJO_DEFINE_POINTER_LIST_TYPEDEFS(CLASS) \
	using CLASS##SPList = std::list<CLASS##SP>;\
	using CLASS##WPList = std::list<CLASS##WP>;

#define MOJO_DEFINE_POINTER_VECTOR_TYPEDEFS(CLASS) \
	using CLASS##SPVec = std::vector<CLASS##SP>;\
	using CLASS##WPVec = std::vector<CLASS##WP>;

#define MOJO_DEFINE_ALL_TYPEDEFS(CLASS) \
	MOJO_DEFINE_POINTER_TYPEDEFS(CLASS) \
	MOJO_DEFINE_POINTER_SET_TYPEDEFS(CLASS) \
	MOJO_DEFINE_POINTER_LIST_TYPEDEFS(CLASS) \
	MOJO_DEFINE_POINTER_VECTOR_TYPEDEFS(CLASS)

#endif // MOJO_CORE_SMART_POINTER_MACROS_H
