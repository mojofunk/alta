#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_moodycamel_queue
#endif

#include "test_includes.hpp"

struct InstanceCounter {
	InstanceCounter () { ++s_count;}
	InstanceCounter (const InstanceCounter& other) { ++s_count;}

	~InstanceCounter () { --s_count;}

	static atomic<int>& count() { return s_count; }
private:

	static atomic<int> s_count;
};

atomic<int> InstanceCounter::s_count(0);

BOOST_AUTO_TEST_CASE(test_moodycamel_queue_hello)
{
	moodycamel::ConcurrentQueue<int> q;

	for (int i = 0; i != 123; ++i)
		q.enqueue(i);

	int item;
	for (int i = 0; i != 123; ++i) {
		q.try_dequeue(item);
		BOOST_CHECK(item == i);
	}
}

BOOST_AUTO_TEST_CASE(test_moodycamel_queue_concurrency)
{
	moodycamel::ConcurrentQueue<int> q;
	int dequeued[100] = { 0 };
	std::thread threads[20];

	// Producers
	for (int i = 0; i != 10; ++i) {
		threads[i] = std::thread([&](int i) {
			                         for (int j = 0; j != 10; ++j) {
				                         q.enqueue(i * 10 + j);
			                         }
			                        },
		                         i);
	}

	// Consumers
	for (int i = 10; i != 20; ++i) {
		threads[i] = std::thread([&]() {
			int item;
			for (int j = 0; j != 20; ++j) {
				if (q.try_dequeue(item)) {
					++dequeued[item];
				}
			}
		});
	}

	// Wait for all threads
	for (int i = 0; i != 20; ++i) {
		threads[i].join();
	}

	// Collect any leftovers (could be some if e.g. consumers finish before
	// producers)
	int item;
	while (q.try_dequeue(item)) {
		++dequeued[item];
	}

	// Make sure everything went in and came back out!
	for (int i = 0; i != 100; ++i) {
		BOOST_CHECK(dequeued[i] == 1);
	}
}

BOOST_AUTO_TEST_CASE(test_moodycamel_queue_concurrency_bulk)
{
	moodycamel::ConcurrentQueue<int> q;
	int dequeued[100] = { 0 };
	std::thread threads[20];

	// Producers
	for (int i = 0; i != 10; ++i) {
		threads[i] = std::thread([&](int i) {
			                         int items[10];
			                         for (int j = 0; j != 10; ++j) {
				                         items[j] = i * 10 + j;
			                         }
			                         q.enqueue_bulk(items, 10);
			                        },
		                         i);
	}

	// Consumers
	for (int i = 10; i != 20; ++i) {
		threads[i] = std::thread([&]() {
			int items[20];
			for (std::size_t count = q.try_dequeue_bulk(items, 20); count != 0;
			     --count) {
				++dequeued[items[count - 1]];
			}
		});
	}

	// Wait for all threads
	for (int i = 0; i != 20; ++i) {
		threads[i].join();
	}

	// Collect any leftovers (could be some if e.g. consumers finish before
	// producers)
	int items[10];
	std::size_t count;
	while ((count = q.try_dequeue_bulk(items, 10)) != 0) {
		for (std::size_t i = 0; i != count; ++i) {
			++dequeued[items[i]];
		}
	}

	// Make sure everything went in and came back out!
	for (int i = 0; i != 100; ++i) {
		BOOST_CHECK(dequeued[i] == 1);
	}
}

BOOST_AUTO_TEST_CASE(test_moodycamel_queue_concurrency_simultaneous)
{
	moodycamel::ConcurrentQueue<InstanceCounter> q;
	const int ProducerCount = 8;
	const int ConsumerCount = 8;
	std::atomic<bool> produce;
	std::thread producers[ProducerCount];
	std::thread consumers[ConsumerCount];
	std::atomic<int> doneProducers(0);
	std::atomic<int> doneConsumers(0);
	for (int i = 0; i != ProducerCount; ++i) {
		producers[i] = std::thread([&]() {
			while (produce) {
				InstanceCounter tmp; // = produce_item();
				q.enqueue(tmp);
			}
			doneProducers.fetch_add(1, std::memory_order_release);
		});
	}
	for (int i = 0; i != ConsumerCount; ++i) {
		consumers[i] = std::thread([&]() {
			InstanceCounter tmp;
			bool itemsLeft;
			do {
				// It's important to fence (if the producers have finished) *before*
				// dequeueing
				itemsLeft = doneProducers.load(std::memory_order_acquire) != ProducerCount;
				while (q.try_dequeue(tmp)) {
					itemsLeft = true;
					// ConsumeItem
				}
			} while (itemsLeft ||
			         doneConsumers.fetch_add(1, std::memory_order_acq_rel) + 1 ==
			             ConsumerCount);
			// The condition above is a bit tricky, but it's necessary to ensure that the
			// last consumer sees the memory effects of all the other consumers before it
			// calls try_dequeue for the last time
		});
	}
	produce = false;
	for (int i = 0; i != ProducerCount; ++i) {
		producers[i].join();
	}
	for (int i = 0; i != ConsumerCount; ++i) {
		consumers[i].join();
	}
	BOOST_CHECK(InstanceCounter::count() == 0);
}

static moodycamel::ConcurrentQueue<shared_ptr<InstanceCounter>> shared_ptr_q;

const int iterations = 1000000;

static std::atomic<int> push_count(0);
static std::atomic<int> pop_count(0);

static std::atomic<bool> done(false);

void produce_foo()
{
	for (int i = 0; i != iterations; ++i) {
		shared_ptr<InstanceCounter> foo_ptr = make_shared<InstanceCounter>();
		shared_ptr_q.enqueue(foo_ptr);
		++push_count;
	}
}

void consume_foo()
{
	shared_ptr<InstanceCounter> foo_ptr;
	int value = 0;
	while (!done) {
		while (shared_ptr_q.try_dequeue(foo_ptr)) {
			++pop_count;
		}
	}

	while (shared_ptr_q.try_dequeue(foo_ptr)) {
		++pop_count;
	}
}


void test_queue_iteration_shared_ptr()
{
	done = false;
	push_count = 0;
	pop_count = 0;

	std::thread t1(produce_foo);
	std::thread t2(produce_foo);
	std::thread t3(produce_foo);
	std::thread t4(consume_foo);
	std::thread t5(consume_foo);
	std::thread t6(consume_foo);

	mojo::sleep(5);

	t1.join();
	t2.join();
	t3.join();
	done = true;
	t4.join();
	t5.join();
	t6.join();

	BOOST_CHECK(push_count == pop_count);
	BOOST_CHECK(InstanceCounter::count() == 0);
	BOOST_CHECK(shared_ptr_q.size_approx() == 0);
}

BOOST_AUTO_TEST_CASE(test_moodycamel_queue_shared_ptr)
{
	for (int i = 0; i < 10; ++i) {
		test_queue_iteration_shared_ptr();
	}
}
