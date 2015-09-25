#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <iostream>
#include <cassert>

using std::endl;
using std::cout;

#include <boost/atomic.hpp>

boost::atomic_int producer_count(0);
boost::atomic_int consumer_count(0);

boost::lockfree::queue<int> queue(128);

const int iterations = 10000000;
const int producer_thread_count = 4;
const int consumer_thread_count = 4;

void producer(void)
{
	for (int i = 0; i != iterations; ++i) {
		int value = ++producer_count;
		while (!queue.push(value))
			;
	}
}

boost::atomic<bool> done(false);

void consumer(void)
{
	int value;
	while (!done) {
		while (queue.pop(value))
			++consumer_count;
	}

	while (queue.pop(value))
		++consumer_count;
}

void test_iteration ()
{
	producer_count = 0;
	consumer_count = 0;

	boost::thread_group producer_threads, consumer_threads;

	for (int i = 0; i != producer_thread_count; ++i)
		producer_threads.create_thread(producer);

	for (int i = 0; i != consumer_thread_count; ++i)
		consumer_threads.create_thread(consumer);

	producer_threads.join_all();
	done = true;

	consumer_threads.join_all();

	cout << "produced " << producer_count << " objects." << endl;
	cout << "consumed " << consumer_count << " objects." << endl;

	assert(producer_count == consumer_count);
}

int main(int argc, char* argv[])
{
	using namespace std;
	cout << "boost::lockfree::queue is ";
	if (!queue.is_lock_free()) cout << "not ";
	cout << "lockfree" << endl;

	for (int i = 0; i < 10; ++i) {
		test_iteration();
	}
}
