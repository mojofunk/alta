#ifndef MOJO_CORE_PRIVATE_H
#define MOJO_CORE_PRIVATE_H

template <typename T>
static inline T*
mojo_get_ptr_helper(T* ptr)
{
	return ptr;
}

#define M_DECLARE_PRIVATE(Class)                                               \
	inline Class##Private* d_func()                                               \
	{                                                                             \
		return reinterpret_cast<Class##Private*>(mojo_get_ptr_helper(d_ptr.get()));  \
	}                                                                             \
	inline const Class##Private* d_func() const                                   \
	{                                                                             \
		return reinterpret_cast<const Class##Private*>(                              \
		    mojo_get_ptr_helper(d_ptr.get()));                                       \
	}                                                                             \
	friend class Class##Private;

#define M_DECLARE_PRIVATE_D(Dptr, Class)                                       \
	inline Class##Private* d_func()                                               \
	{                                                                             \
		return reinterpret_cast<Class##Private*>(Dptr);                              \
	}                                                                             \
	inline const Class##Private* d_func() const                                   \
	{                                                                             \
		return reinterpret_cast<const Class##Private*>(Dptr);                        \
	}                                                                             \
	friend class Class##Private;

#define M_DECLARE_PUBLIC(Class)                                                \
	inline Class* q_func() { return static_cast<Class*>(q_ptr); }                 \
	inline const Class* q_func() const                                            \
	{                                                                             \
		return static_cast<const Class*>(q_ptr);                                     \
	}                                                                             \
	friend class Class;

#define M_D(Class) Class##Private* const d = d_func()
#define M_Q(Class) Class* const q = q_func()

#endif // MOJO_CORE_PRIVATE_H
