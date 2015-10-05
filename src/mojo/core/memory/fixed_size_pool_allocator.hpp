#ifndef MOJO_CORE_FIXED_SIZE_POOL_ALLOCATOR_H
#define MOJO_CORE_FIXED_SIZE_POOL_ALLOCATOR_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/memory/fixed_size_pool.hpp"
#endif

/**
 * All Pool allocators should be MT safe.
 *
 * A FixedSizePool allocator is guaranteed to be lock-free and wait-free but can
 * fail to allocate if pool is empty.
 *
 * A VariableSizePool allocator is lock-free and wait-free unless the pool is
 * empty in which case more memory will be allocated which may not be
 * wait-free. The pool could also shrink if necessary although that may get
 * complicated.
 *
 * The maximum number of instances in the pool is
 * std::numeric_limits<std::uint16_t>::max() as result of boost::lockfree
 */
namespace mojo {

template <typename T>
class FixedSizePoolAllocator {
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
		typedef FixedSizePoolAllocator<U> other;
	};

public:
	inline explicit FixedSizePoolAllocator(const uint16_t size)
	    : m_pool(new FixedSizePool<T>(size))
	{
	}

	inline ~FixedSizePoolAllocator() {}

	inline explicit FixedSizePoolAllocator(const FixedSizePoolAllocator<T>& other)
	    : m_pool(other.m_pool)
	{
	}

#if 0
	template <typename U>
	inline explicit FixedSizePoolAllocator(const FixedSizePoolAllocator<U>&)
	{
	}
#endif

	bool empty() { return m_pool->empty() }

	inline pointer address(reference r) { return &r; }
	inline const_pointer address(const_reference r) { return &r; }

	inline pointer allocate(size_type cnt,
	                        typename std::allocator<void>::const_pointer = 0)
	{
		// only allocations of single count are supported atm
		if (cnt != 1) return nullptr;

		return m_pool->allocate();
	}

	inline void deallocate(pointer p, size_type) { return m_pool->deallocate(p); }

	inline size_type max_size() const { return m_pool->size(); }

	inline void construct(pointer p, const T& t) { new (p) T(t); }

	inline void destroy(pointer p) { p->~T(); }

	inline bool operator==(FixedSizePoolAllocator const&) { return true; }
	inline bool operator!=(FixedSizePoolAllocator const& a) { return !operator==(a); }

private:

	std::shared_ptr<FixedSizePool<T>> m_pool;
};

} // namespace mojo

#endif // MOJO_CORE_FIXED_SIZE_POOL_ALLOCATOR_H
