#ifndef MOJO_CORE_RING_BUFFER_H
#define MOJO_CORE_RING_BUFFER_H

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

	size_t read_available() const
	{
		// relaxed as only written from read thread
		size_t r = m_read_index.load(std::memory_order_relaxed);
		size_t w = m_write_index.load(std::memory_order_acquire);

		return read_available(r, w);
	}

	size_t write_available() const
	{
		// relaxed as only written from write thread
		size_t w = m_write_index.load(std::memory_order_relaxed);
		size_t r = m_read_index.load(std::memory_order_acquire);

		return write_available(r, w);
	}

	size_t max_write_count() const { return m_size - 1; }

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

	void increment_read_index(size_t count)
	{
		// TODO? use load/relaxed and store/release
		m_read_index = (m_read_index + count) % m_size;
	}

	void increment_write_index(size_t count)
	{
		// TODO? use load/relaxed and store/release
		m_write_index = (m_write_index + count) % m_size;
	}

	std::unique_ptr<T[]> m_buffer;

	std::atomic<size_t> m_read_index;
	std::atomic<size_t> m_write_index;

protected: // Methods
	bool empty(size_t read_index, size_t write_index)
	{
		return read_index == write_index;
	}

	size_t read_available(size_t read_index, size_t write_index) const
	{
		if (write_index > read_index) {
			return write_index - read_index;
		} else {
			return (write_index - read_index + m_size) % m_size;
		}
	}

	size_t write_available(size_t read_index, size_t write_index) const
	{
		if (write_index > read_index) {
			return ((read_index - write_index + m_size) % m_size) - 1;
		} else if (write_index < read_index) {
			return (read_index - write_index) - 1;
		} else {
			return m_size - 1;
		}
	}

private: // Data
	size_t const m_size;
};

template <class T>
typename RingBuffer<T>::Vectors RingBuffer<T>::get_read_vectors()
{
	RingBuffer<T>::Vectors v;

	const size_t write_index = m_write_index.load(std::memory_order_acquire);
	const size_t read_index = m_read_index.load(std::memory_order_relaxed);

	size_t read_avail = read_available(read_index, write_index);

	if (read_avail == 0) {
		return v;
	}

	size_t new_read_index = read_index + read_avail;

	if (new_read_index > m_size) {
		// two part vector
		v.vec1 = &m_buffer[read_index];
		v.size1 = m_size - read_index;
		v.vec2 = m_buffer.get();
		v.size2 = new_read_index % m_size;
		assert(v.size1 + v.size2 == read_avail);
	} else {
		// single vector
		v.vec1 = &m_buffer[read_index];
		v.size1 = read_avail;
	}

	return v;
}

template <class T>
typename RingBuffer<T>::Vectors RingBuffer<T>::get_write_vectors()
{
	RingBuffer<T>::Vectors v;

	const size_t write_index = m_write_index.load(std::memory_order_relaxed);
	const size_t read_index = m_read_index.load(std::memory_order_acquire);

	size_t write_avail = write_available(read_index, write_index);

	if (write_avail == 0) {
		return v;
	}

	size_t new_write_index = write_index + write_avail;

	if (new_write_index > m_size) {
		// two part vector
		v.vec1 = &m_buffer[write_index];
		v.size1 = m_size - write_index;
		v.vec2 = m_buffer.get();
		v.size2 = new_write_index % m_size;
		assert(v.size1 + v.size2 == write_avail);
	} else {
		// single vector
		v.vec1 = &m_buffer[write_index];
		v.size1 = write_avail;
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

	increment_read_index(count);

	return count;
}

template <class T>
size_t RingBuffer<T>::write(const T* src, size_t count)
{
	Vectors wv = get_write_vectors();

	// guard against reading more than possible
	if (count > wv.size()) {
		count = wv.size();
	}

	if (count <= wv.size1) {
		// just write to first vector
		memcpy(wv.vec1, src, count * sizeof(T));
	} else {
		// write to both vectors
		memcpy(wv.vec1, src, wv.size1 * sizeof(T));
		memcpy(wv.vec2, src + wv.size1, (count - wv.size1) * sizeof(T));
	}

	increment_write_index(count);

	return count;
}

#endif // MOJO_CORE_RING_BUFFER_H
