#ifndef MOJO_CORE_FIXED_SIZE_OBJECT_POOL_H
#define MOJO_CORE_FIXED_SIZE_OBJECT_POOL_H

namespace mojo {

template <class T>
class FixedSizeObjectPool {
public:
	FixedSizeObjectPool(const uint16_t count)
	    : m_fixed_pool(sizeof(T), count)
	{
	}

	~FixedSizeObjectPool() {}

	// return true if allocated by pool
	bool is_from(T* ptr) const { return m_fixed_pool.is_from((void*)ptr); }

	T* allocate()
	{
		return reinterpret_cast<T*>(m_fixed_pool.allocate(sizeof(T)));
	}

	void deallocate(T* ptr) { m_fixed_pool.deallocate((void*)ptr); }

	bool empty() const { return m_fixed_pool.empty(); }

	uint16_t available() const { return m_fixed_pool.available(); }

	uint16_t count() const { return m_fixed_pool.count(); }

private:
	FixedSizePool m_fixed_pool;
};

} // namespace mojo

#endif // MOJO_CORE_FIXED_SIZE_OBJECT_POOL_H
