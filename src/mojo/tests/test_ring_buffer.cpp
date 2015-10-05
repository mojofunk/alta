#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_ring_buffer
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <thread>

#include "mojo/core/time/time.hpp"

#include "mojo/core/lockfree/ring_buffer.hpp"
#include "mojo/core/string/compose.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

template <class T>
void print_read_vectors(RingBuffer<T>& rb)
{
	typename RingBuffer<T>::Vectors rv = rb.get_read_vectors();

	BOOST_TEST_MESSAGE(
	    compose("Read Vectors: vec1 = %, size1 = %, vec2 = %, size2 = %",
	            rb.offset(rv.vec1),
	            rv.size1,
	            rb.offset(rv.vec2),
	            rv.size2));
}

template <class T>
void print_write_vectors(RingBuffer<T>& rb)
{
	typename RingBuffer<T>::Vectors rv = rb.get_write_vectors();

	BOOST_TEST_MESSAGE(
	    compose("Write Vectors: vec1 = %, size1 = %, vec2 = %, size2 = %",
	            rb.offset(rv.vec1),
	            rv.size1,
	            rb.offset(rv.vec2),
	            rv.size2));
}

BOOST_AUTO_TEST_CASE(test_ring_buffer_basic)
{
	size_t buffer_size = 64;
	size_t half_buffer_size = buffer_size / 2;

	RingBuffer<float> rbl(buffer_size);
	size_t max_write_count = rbl.max_write_count();

	BOOST_CHECK(rbl.write_available() == max_write_count);
	BOOST_CHECK(rbl.read_available() == 0);

	size_t write_count = half_buffer_size;

	// check write vectors, should only be one, the whole buffer
	RingBuffer<float>::Vectors wv = rbl.get_write_vectors();

	print_write_vectors(rbl);

	BOOST_CHECK(wv.size() == max_write_count);
	BOOST_CHECK(wv.vec1 == rbl.m_buffer.get());
	BOOST_CHECK(wv.size1 == max_write_count);
	BOOST_CHECK(wv.vec2 == nullptr);
	BOOST_CHECK(wv.size2 == 0);

	unique_ptr<float[]> write_buf(new float[buffer_size]);

	// write junk into ~half the buffer
	BOOST_CHECK(rbl.write(write_buf.get(), write_count) == write_count);

	BOOST_CHECK(write_count == rbl.read_available());

	// check read vectors, should only be one

	RingBuffer<float>::Vectors rv = rbl.get_read_vectors();

	print_read_vectors(rbl);

	BOOST_CHECK(rv.size() == write_count);
	BOOST_CHECK(rv.vec1 == rbl.m_buffer.get());
	BOOST_CHECK(rv.size1 == write_count);
	BOOST_CHECK(rv.vec2 == nullptr);
	BOOST_CHECK(rv.size2 == 0);

	unique_ptr<float[]> read_buf(new float[buffer_size]);

	// read junk data and test that it is the same as what was written
	BOOST_CHECK(rbl.read(read_buf.get(), write_count) == write_count);

	BOOST_CHECK(rbl.read_available() == 0);

	print_read_vectors(rbl);

	for (int i = 0; i < write_count; ++i) {
		BOOST_CHECK(read_buf[i] == write_buf[i]);
	}

	wv = rbl.get_write_vectors();
	print_write_vectors(rbl);

	// check write vector, should be two parts
	BOOST_CHECK(wv.size() == max_write_count);
	BOOST_CHECK(wv.vec1 != nullptr);
	BOOST_CHECK(wv.size1 != 0);
	BOOST_CHECK(wv.vec2 != nullptr);
	BOOST_CHECK(wv.size2 != 0);
	BOOST_CHECK(wv.size1 + wv.size2 == wv.size());

	write_count = max_write_count;

	// write junk into the maximum write amount
	BOOST_CHECK(rbl.write(write_buf.get(), write_count) == write_count);

	print_read_vectors(rbl);

	rv = rbl.get_read_vectors();

	BOOST_CHECK(rv.size() == write_count);
	BOOST_CHECK(rv.vec1 != nullptr);
	BOOST_CHECK(rv.size1 != 0);
	BOOST_CHECK(rv.vec2 != nullptr);
	BOOST_CHECK(rv.size2 != 0);

	BOOST_CHECK(rbl.write_available() == 0);
}

BOOST_AUTO_TEST_CASE(test_ring_buffer_bounds)
{
	// test for writing out of buffer bounds
}

BOOST_AUTO_TEST_CASE(test_ring_buffer_random)
{
	size_t buffer_size = g_random_int_range(1, 4096);
	RingBuffer<int> rbl(buffer_size);
	size_t total_write_count = 0;
	size_t total_read_count = 0;

	for (int i = 0; i != 10; ++i) {

		size_t write_count = g_random_int_range(1, rbl.write_available());

		RingBuffer<int>::Vectors wv = rbl.get_write_vectors();
		BOOST_CHECK(wv.size() == rbl.write_available());

		print_write_vectors(rbl);

		unique_ptr<int[]> write_buf(new int[write_count]);

		for (int i = 0; i < write_count; ++i) {
			write_buf[g_random_int_range(-100, 100)];
		}

		BOOST_CHECK(rbl.write(write_buf.get(), write_count) == write_count);

		BOOST_CHECK(write_count == rbl.read_available());

		total_write_count += write_count;

		RingBuffer<int>::Vectors rv = rbl.get_read_vectors();
		BOOST_CHECK(rv.size() == write_count);

		print_read_vectors(rbl);

		unique_ptr<int[]> read_buf(new int[write_count]);

		BOOST_CHECK(rbl.read(read_buf.get(), write_count) == write_count);
		BOOST_CHECK(rbl.read_available() == 0);
		total_read_count += write_count;

		for (int i = 0; i < write_count; ++i) {
			BOOST_CHECK(read_buf[i] == write_buf[i]);
		}
	}
	BOOST_CHECK(total_read_count == total_write_count);
}

const int32_t BUFFER_SIZE = 1024;

RingBuffer<uint32_t> rb(BUFFER_SIZE);

std::atomic_bool s_producer_exit(false);
std::atomic_bool s_consumer_exit(false);

uint32_t total_written = 0;
uint32_t total_read = 0;

static bool producer_thread_failed = false;

void producer_thread()
{
	while (!s_producer_exit) {
		if (rb.write_available() == 0) {
			uint32_t sleep_count = g_random_int_range(10, 100);
#if 0
			BOOST_TEST_MESSAGE(
			    compose("Write space 0, sleeping for %(ns)", sleep_count));
#endif
			mojo::usleep(sleep_count);
			continue;
		}
		size_t write_cnt = g_random_int_range(0, rb.write_available());
		if (write_cnt == 0) continue;
		uint32_t* write_array = new uint32_t[write_cnt];
		// write random data
		bool success = (rb.write(write_array, write_cnt) == write_cnt);
		if (success) {
			total_written += write_cnt;
		} else {
			producer_thread_failed = true;
		}
#if 0
		BOOST_TEST_MESSAGE(compose("Wrote % units to RingBuffer, Total Written: %",
		                           write_cnt,
		                           total_written));
#endif
		delete[] write_array;
	}
}

static bool consumer_thread_failed = false;

void consumer_thread()
{
	while (!s_consumer_exit) {
		if (rb.read_available() == 0) {
			uint32_t sleep_count = g_random_int_range(10, 100);
#if 0
			BOOST_TEST_MESSAGE(compose("Read count 0, sleeping for %(ns)", sleep_count));
#endif
			mojo::usleep(sleep_count);
			continue;
		}
		size_t read_cnt = g_random_int_range(0, rb.read_available());
		if (read_cnt == 0) continue;
		uint32_t* read_array = new uint32_t[read_cnt];
		bool success = (rb.read(read_array, read_cnt) == read_cnt);
		if (success) {
			total_read += read_cnt;
		} else {
			consumer_thread_failed = true;
		}
#if 0
		BOOST_TEST_MESSAGE(compose(
		    "Read % units from RingBuffer, Total Read: %", read_cnt, total_read));
#endif
		delete[] read_array;
	}

	// read any remaining data
	size_t read_cnt = rb.read_available();
	uint32_t* read_array = new uint32_t[read_cnt];
	bool success = (rb.read(read_array, read_cnt) == read_cnt);
	if (success) {
		total_read += read_cnt;
	} else {
		consumer_thread_failed = true;
	}
}

BOOST_AUTO_TEST_CASE(test_ring_buffer_threaded)
{
	std::thread producer(producer_thread);
	std::thread consumer(consumer_thread);

	mojo::sleep(10);

	s_producer_exit = true;
	producer.join();

	s_consumer_exit = true;
	consumer.join();

	BOOST_TEST_MESSAGE(
	    compose("Total Written %, Total Read %", total_written, total_read));
	BOOST_CHECK(total_written == total_read);
}
