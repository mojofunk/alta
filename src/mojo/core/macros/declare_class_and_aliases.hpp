#define M_DECLARE_CLASS_AND_POINTER_ALIASES(ClassName)                         \
	class ClassName;                                                              \
	MOJO_DEFINE_POINTER_TYPEDEFS(ClassName);

#define M_DECLARE_CLASS_AND_ALL_ALIASES(ClassName)                             \
	class ClassName;                                                              \
	MOJO_DEFINE_ALL_TYPEDEFS(ClassName);
