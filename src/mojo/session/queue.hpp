#ifndef MOJO_QUEUE
#define MOJO_QUEUE

#include <queue>

#include <boost/function.hpp>

namespace mojo {

namespace internal {

class Queue
{
public:
	typedef boost::function<void()> function_t;

	void push (const function_t& func)
	{
		m_queue.push (func);
	}

	function_t pop ()
	{
		function_t func;

		func = m_queue.front ();
		m_queue.pop ();
		return func;
	}

private:

	std::queue<boost::function<void()> > m_queue;

};

} // namespace internal

} // namespace mojo

#endif
