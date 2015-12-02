
#include "dispatcher.hpp"

#include "log.hpp"

namespace ui {

Dispatcher::Dispatcher()
{
}

void Dispatcher::run()
{
	{
		m_iter_sema.wait();

		do_work();

		{
			std::unique_lock<std::mutex> lock(m_iter_mtx);

			m_cond.notify_one();
		}
	}
}

void Dispatcher::iteration(bool block)
{
	if (block) {
		std::unique_lock<std::mutex> lock(m_iter_mtx);

		// thread safe?
		Glib::signal_idle().connect(
		    sigc::bind_return(sigc::mem_fun(*this, &Dispatcher::run), false));

		// signal to run
		m_iter_sema.post();

		// wait for one iteration to complete
		m_cond.wait(lock);
	} else {
		// thread safe?
		Glib::signal_idle().connect(
		    sigc::bind_return(sigc::mem_fun(*this, &Dispatcher::run), false));
		m_iter_sema.post();
	}
}

void Dispatcher::call_sync(const function_t& func)
{
	LOG;
	queue(func);
	iteration(true);
}

void Dispatcher::call_async(const function_t& func)
{
	LOG;
	queue(func);
	iteration(false);
}

void Dispatcher::queue(const function_t& func)
{
	std::unique_lock<std::mutex> lock(m_queue_lock);
	m_queue.push(func);
}

void Dispatcher::do_work()
{
	LOG;
	process_queue();
}

void Dispatcher::process_queue()
{
	std::unique_lock<std::mutex> lock(m_queue_lock);

	while (!m_queue.empty()) {

		function_t func = m_queue.front();
		m_queue.pop();

		// unlock while executing
		m_queue_lock.unlock();
		LOG;
		func();
		m_queue_lock.lock();
	}
}
}
