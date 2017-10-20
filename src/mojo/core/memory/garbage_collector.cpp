// TODO proper logging
void
GarbageCollector::run()
{
	// create a vector to hold the contents of the queue, not a good design in
	// terms of minimizing memory usage etc but it will do for now
	std::vector<std::shared_ptr<void>> vec;
	std::size_t queue_size = m_gc_queue.size_approx();
	vec.reserve(queue_size);
	std::shared_ptr<void> tmp_ptr;

	// queue_size prevents a live lock in the situation where one thread is
	// dequeuing while another thread is re-enqueuing below
	while (queue_size != 0 && m_gc_queue.try_dequeue(tmp_ptr)) {
		vec.push_back(tmp_ptr);
		--queue_size;
	}

	tmp_ptr.reset();

	// std::cout << "GC::run dequeued: " << vec.size() << std::endl;

	int reenqueue_count = 0;

	for (auto& ptr : vec) {
		// If the instance_ptr is unique then reset it to call the destructor,
		// otherwise push it back onto the queue.
		if (ptr.unique()) {
			// std::cout << "resetting ptr" << ptr.get() << std::endl;
			ptr.reset();
		} else {
			// std::cout << "GC::run reenqueueing" << ptr.get()
			//          << " use_count = " << ptr.use_count() << std::endl;
			reenqueue_count++;
			m_gc_queue.enqueue(ptr);
		}
	}
	// std::cout << "GC::run reenqueued count: " << reenqueue_count << std::endl;
}
