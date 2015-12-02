#ifndef GLEAM_ASYNC_SIGNAL_H
#define GLEAM_ASYNC_SIGNAL_H

template <class T>
class AsyncSignal {
public:
	AsyncSignal();

	void send(const T&);

	sigc::signal<void, const T*> signal_async() { return m_signal; }

	bool caller_is_my_thread() const
	{
		if (Glib::Thread::self() == m_thread) {
			return true;
		}

		return false;
	}

private:
	sigc::signal<void, const T*> m_signal;

	Glib::Dispatcher m_dispatcher;
	Glib::Mutex m_mutex;
	const Glib::Thread* const m_thread;

	std::queue<T> m_event_queue;

	void dispatch_handler();
};

template <class T>
AsyncSignal<T>::AsyncSignal()
    : m_thread(Glib::Thread::self())
{
	m_dispatcher.connect(mem_fun(*this, &AsyncSignal<T>::dispatch_handler));
}

template <class T>
void AsyncSignal<T>::send(const T& event)
{
	if (caller_is_my_thread()) {
		// no need to copy
		m_signal(&event);
	} else {
		Glib::Mutex::Lock guard(m_mutex);

		m_event_queue.push(event);

		m_dispatcher.emit();
	}
}

template <class T>
void AsyncSignal<T>::dispatch_handler()
{
	Glib::Mutex::Lock guard(m_mutex);

	while (!m_event_queue.empty()) {
		const T event = m_event_queue.front();
		m_event_queue.pop();

		m_mutex.unlock();

		m_signal(&event);

		m_mutex.lock();
	}
}

#endif // GLEAM_ASYNC_SIGNAL_H
