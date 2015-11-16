#ifndef MOJO_CORE_SMART_POINTERS_H
#define MOJO_CORE_SMART_POINTERS_H

#define M_DEFINE_POINTER_TYPEDEFS(Class)                                       \
	using Class##SP = std::shared_ptr<Class>;                                     \
	using Class##WP = std::weak_ptr<Class>;                                       \
	using Class##ConstSP = std::shared_ptr<Class const>;                          \
	using Class##ConstWP = std::weak_ptr<Class const>;

#define M_DEFINE_POINTER_SET_TYPEDEFS(Class)                                   \
	using Class##SPSet = std::set<Class##SP>;                                     \
	using Class##WPSet = std::set<Class##WP>;

#define M_DEFINE_POINTER_LIST_TYPEDEFS(Class)                                  \
	using Class##SPList = std::list<Class##SP>;                                   \
	using Class##WPList = std::list<Class##WP>;

#define M_DEFINE_POINTER_VECTOR_TYPEDEFS(Class)                                \
	using Class##SPVec = std::vector<Class##SP>;                                  \
	using Class##WPVec = std::vector<Class##WP>;

#define M_DEFINE_ALL_TYPEDEFS(Class)                                           \
	M_DEFINE_POINTER_TYPEDEFS(Class)                                              \
	M_DEFINE_POINTER_SET_TYPEDEFS(Class)                                          \
	M_DEFINE_POINTER_LIST_TYPEDEFS(Class)                                         \
	M_DEFINE_POINTER_VECTOR_TYPEDEFS(Class)

#endif // MOJO_CORE_SMART_POINTERS_H
