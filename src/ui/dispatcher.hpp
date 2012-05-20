
#ifndef UI_DISPATCHER
#define UI_DISPATCHER

#include <queue>

#include <sigc++/signal.h>

#include <glibmm/thread.h>
#include <glibmm/dispatcher.h>

#include <gleam/gleam.hpp>

namespace ui {

class Dispatcher
{
public: // typedefs

	typedef sigc::slot<void> function_t;

public: // ctor

	Dispatcher ();

public: // api

	void call_sync (const function_t& func);

	void call_async (const function_t& func);

private:

	void run ();

	void do_work ();

	void iteration(bool block = false);

	void queue (const function_t& func);

	void process_queue ();

private: // members

	Glib::Mutex                     m_iter_mtx;
	Glib::Mutex                     m_queue_lock;
	Glib::Cond                      m_cond;

	gleam::Semaphore                m_iter_sema;

	std::queue<function_t>          m_queue;

};


} // namespace ui

#endif
