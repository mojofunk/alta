#ifndef MOJO_CORE_LOG_ALLOCATOR_H
#define MOJO_CORE_LOG_ALLOCATOR_H

template <typename T>
class LogAllocator {
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

public:
	template <typename U>
	struct rebind {
		typedef LogAllocator<U> other;
	};

public:
	inline LogAllocator(){}; // = default

	inline ~LogAllocator() {}

	inline explicit LogAllocator(const LogAllocator<T>& other) {}

	template <typename U>
	inline LogAllocator(const LogAllocator<U>&)
	{
	}

	bool empty() { return false; }

	inline pointer address(reference r) { return &r; }
	inline const_pointer address(const_reference r) { return &r; }

	inline pointer allocate(size_type cnt,
	                        typename std::allocator<void>::const_pointer = 0)
	{
		if (cnt <= std::numeric_limits<std::size_t>::max() / sizeof(T)) {
			void* ptr = log_malloc(cnt * sizeof(T));
			if (ptr) {
				return static_cast<T*>(ptr);
			}
		}
		throw std::bad_alloc();
	}

	inline void deallocate(pointer ptr, size_type cnt) { log_free(ptr); }

	inline size_type max_size() const
	{
		return std::numeric_limits<std::size_t>::max() / sizeof(T);
	}

	inline void construct(pointer p, const T& t) { new (p) T(t); }

	inline void destroy(pointer p) { p->~T(); }

#if 0
	inline bool operator==(const LogAllocator&) { return true; }
	inline bool operator!=(const LogAllocator& a) { return !operator==(a); }
#endif

	template <class U1, class U2>
	friend bool operator==(const LogAllocator<U1>& x,
	                       const LogAllocator<U2>& y) noexcept;

	template <class U>
	friend class LogAllocator;
};

template <class U1, class U2>
inline bool operator==(const LogAllocator<U1>& x,
                       const LogAllocator<U2>& y) noexcept
{
	return true;
}

template <class U1, class U2>
inline bool operator!=(const LogAllocator<U1>& x,
                       const LogAllocator<U2>& y) noexcept
{
	return !(x == y);
}

#endif // MOJO_CORE_LOG_ALLOCATOR_H
