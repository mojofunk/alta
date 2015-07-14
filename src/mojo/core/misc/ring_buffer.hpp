#ifndef MOJO_CORE_RING_BUFFER_H
#define MOJO_CORE_RING_BUFFER_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

// TODO use allocator
template <class T>
class RingBuffer {
public:
	RingBuffer(size_t size)
	    : m_size(size)
	    , m_read_index(0)
	    , m_write_index(0)
	{
		m_buffer.reset(new T[size]);
	}

	~RingBuffer() {}

	size_t read(T* dest, size_t count);
	size_t write(const T* src, size_t count);

	size_t read_count() const
	{
		size_t r = m_read_index;
		size_t w = m_write_index;

		if (w > r) {
			return w - r;
		} else {
			return (w - r + m_size) % m_size;
		}
	}

	size_t write_space() const
	{
		size_t r = m_read_index;
		size_t w = m_write_index;

		if (w > r) {
			return ((r - w + m_size) % m_size) - 1;
		} else if (w < r) {
			return (r - w) - 1;
		} else {
			return m_size - 1;
		}
	}

	struct Vectors {
		Vectors()
		    : vec1(nullptr)
		    , vec2(nullptr)
		    , size1(0)
		    , size2(0)
		{
		}

		size_t size() { return size1 + size2; }

		T* vec1;
		T* vec2;
		size_t size1;
		size_t size2;
	};

	uint32_t offset(T* ptr) const { return ptr - m_buffer.get(); }

	Vectors get_read_vectors();
	Vectors get_write_vectors();

	std::unique_ptr<T[]> m_buffer;

	std::atomic<size_t> m_read_index;
	std::atomic<size_t> m_write_index;

protected:
	size_t const m_size;
};

template <class T>
typename RingBuffer<T>::Vectors RingBuffer<T>::get_read_vectors()
{
	RingBuffer<T>::Vectors v;

	size_t w = m_write_index;
	size_t r = m_read_index;
	size_t free_count = 0;

	if (w > r) {
		free_count = w - r;
	} else {
		free_count = (w - r + m_size) % m_size;
	}

	size_t cnt = r + free_count;

	if (cnt > m_size) {
		// two part vector
		v.vec1 = &m_buffer[r];
		v.size1 = m_size - r;
		v.vec2 = m_buffer.get();
		v.size2 = cnt % m_size;
	} else {
		// single vector
		v.vec1 = &m_buffer[r];
		v.size1 = cnt;
	}

	return v;
}

template <class T>
typename RingBuffer<T>::Vectors RingBuffer<T>::get_write_vectors()
{
	RingBuffer<T>::Vectors v;

	size_t w = m_write_index;
	size_t r = m_read_index;
	size_t free_count = 0;

	if (w > r) {
		// read index before write index
		// two part vector
		// m_size - (w - r) - 1?
		free_count = ((r - w + m_size) % m_size) - 1;
	} else if (w < r) {
		// one part vector
		// empty between write index and read index
		free_count = (r - w) - 1;
	} else {
		// single vector
		// only occurs when buffer initially empty
		free_count = m_size - 1;
	}

	size_t cnt = w + free_count;

	if (cnt > m_size) {
		// two part vector
		v.vec1 = &m_buffer[w];
		v.size1 = m_size - w;
		v.vec2 = m_buffer.get();
		v.size2 = cnt % m_size;
	} else {
		// single vector
		v.vec1 = &m_buffer[w];
		v.size1 = cnt;
	}

	return v;
}

template <class T>
size_t RingBuffer<T>::read(T* dest, size_t count)
{
	Vectors rv = get_read_vectors();

	// guard against reading more than possible
	if (count > rv.size()) {
		count = rv.size();
	}

	if (count <= rv.size1) {
		// just read from first vector
		memcpy(dest, rv.vec1, count * sizeof(T));
	} else {
		// read from both vectors
		memcpy(dest, rv.vec1, rv.size1 * sizeof(T));
		memcpy(dest + rv.size1, rv.vec2, (count - rv.size1) * sizeof(T));
	}

	m_read_index = (m_read_index + count) % m_size;

	return count;
}

template <class T>
size_t RingBuffer<T>::write(const T* src, size_t count)
{
	Vectors rv = get_write_vectors();

	// guard against reading more than possible
	if (count > rv.size()) {
		count = rv.size();
	}

	if (count <= rv.size1) {
		// just write to first vector
		memcpy(rv.vec1, src, count * sizeof(T));
	} else {
		// write to both vectors
		memcpy(rv.vec1, src, rv.size1 * sizeof(T));
		memcpy(rv.vec2, src + rv.size1, (count - rv.size1) * sizeof(T));
	}

	m_write_index = (m_write_index + count) % m_size;

	return count;
}

} // namespace mojo

#endif // MOJO_CORE_RING_BUFFER_H
