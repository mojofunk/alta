#ifndef MOJO_APPLICATION_DATA_H
#define MOJO_APPLICATION_DATA_H

namespace internal
{

class WorkerThread
{
public:
	typedef std::function<void()> function_t;

	WorkerThread()
	    : m_thread(std::ref(*this))
	{
		// wait for dispatcher to start
		// m_dispatcher.iteration(true);
	}

	~WorkerThread()
	{
		m_dispatcher.quit();
		m_thread.join();
	}

	void operator()() { m_dispatcher.run(); }

	void call_sync(const function_t& func) { m_dispatcher.call_sync(func); }

	void call_async(const function_t& func) { m_dispatcher.call_async(func); }

	void iteration(bool block) { m_dispatcher.iteration(block); }

private:
	FunctorDispatcher m_dispatcher;

	std::thread m_thread;
};

struct ApplicationData {
	ProjectSPSet projects;

	Project* active_project;

	WorkerThread worker;

	// going to need a per project lock for access to
	// project data from worker thread and from client
	// when data is needed syncronously.

	ModuleSPSet m_modules;

	signals::signal<void(Project*)> m_project_added;
	signals::signal<void(Project*)> m_project_removed;
};

} // namespace internal

#endif // MOJO_APPLICATION_DATA_H
