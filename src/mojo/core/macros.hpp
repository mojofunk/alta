#ifndef MOJO_CORE_MACROS
#define MOJO_CORE_MACROS

#include <set>
#include <vector>
#include <list>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#define MOJO_DEFINE_POINTER_TYPEDEFS(CLASS) \
	typedef boost::shared_ptr<CLASS>    CLASS##SP;\
	typedef boost::weak_ptr<CLASS>      CLASS##WP;\
	typedef boost::shared_ptr<CLASS const>    CLASS##ConstSP;\
	typedef boost::weak_ptr<CLASS const>      CLASS##ConstWP;

#define MOJO_DEFINE_POINTER_SET_TYPEDEFS(CLASS) \
	typedef std::set<CLASS##SP>         CLASS##SPSet;\
	typedef std::set<CLASS##WP>         CLASS##WPSet;

#define MOJO_DEFINE_POINTER_LIST_TYPEDEFS(CLASS) \
	typedef std::list<CLASS##SP>         CLASS##SPList;\
	typedef std::list<CLASS##WP>         CLASS##WPList;

#define MOJO_DEFINE_POINTER_VECTOR_TYPEDEFS(CLASS) \
	typedef std::vector<CLASS##SP>         CLASS##SPVec;\
	typedef std::vector<CLASS##WP>         CLASS##WPVec;

#endif
