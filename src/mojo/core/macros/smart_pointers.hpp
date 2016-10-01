#ifndef MOJO_CORE_SMART_POINTERS_H
#define MOJO_CORE_SMART_POINTERS_H

#define MOJO_DEFINE_POINTER_TYPEDEFS(Class)                                    \
	using Class##UP = std::unique_ptr<Class>;                                     \
	using Class##SP = std::shared_ptr<Class>;                                     \
	using Class##WP = std::weak_ptr<Class>;                                       \
	using Class##ConstUP = std::unique_ptr<Class const>;                          \
	using Class##ConstSP = std::shared_ptr<Class const>;                          \
	using Class##ConstWP = std::weak_ptr<Class const>;

#define MOJO_DEFINE_POINTER_SET_TYPEDEFS(Class)                                \
	using Class##UPSet = std::set<Class##UP>;                                     \
	using Class##SPSet = std::set<Class##SP>;                                     \
	using Class##WPSet = std::set<Class##WP>;

#define MOJO_DEFINE_POINTER_LIST_TYPEDEFS(Class)                               \
	using Class##UPList = std::list<Class##UP>;                                   \
	using Class##SPList = std::list<Class##SP>;                                   \
	using Class##WPList = std::list<Class##WP>;

#define MOJO_DEFINE_POINTER_VECTOR_TYPEDEFS(Class)                             \
	using Class##UPVec = std::vector<Class##UP>;                                  \
	using Class##SPVec = std::vector<Class##SP>;                                  \
	using Class##WPVec = std::vector<Class##WP>;

#define MOJO_DEFINE_ALL_TYPEDEFS(Class)                                        \
	MOJO_DEFINE_POINTER_TYPEDEFS(Class)                                           \
	MOJO_DEFINE_POINTER_SET_TYPEDEFS(Class)                                       \
	MOJO_DEFINE_POINTER_LIST_TYPEDEFS(Class)                                      \
	MOJO_DEFINE_POINTER_VECTOR_TYPEDEFS(Class)

#endif // MOJO_CORE_SMART_POINTERS_H
