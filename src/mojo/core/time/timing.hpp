#ifndef MOJO_CORE_TIMING_H
#define MOJO_CORE_TIMING_H

#include <cstdint>

#include <string>
#include <vector>

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/visibility.hpp"
#include "mojo/core/time/time.hpp"
#endif

namespace mojo {

MOJO_API bool get_min_max_avg_total (const std::vector<uint64_t>& values, uint64_t& min, uint64_t& max, uint64_t& avg, uint64_t& total);

MOJO_API std::string timing_summary (const std::vector<uint64_t>& values);

/**
 * This class allows collecting timing data using two different
 * techniques. The first is using start() and update() and then
 * calling elapsed() to get the elapsed time. This is useful when
 * you want to measure the elapsed time between two different
 * execution points. e.g
 *
 * timing.start();
 * do_stuff();
 * timing.update();
 * cerr << "do_stuff took: "
 *      << timing.elapsed()
 *      << "usecs" << endl;
 *
 * The other is timing intervals using start() and calling
 * get_interval() periodically to measure the time intervals
 * between the same execution point. The difference is necessary
 * to get the most accurate timing information when timing
 * intervals but I didn't feel it necessary to have two separate
 * classes.
 */
class MOJO_API Timing
{
public:

	Timing ()
		: m_start_val(0)
		, m_last_val(0)
	{ start ();}

	bool valid () const {
		return (m_start_val != 0 && m_last_val != 0) &&
		       (m_start_val < m_last_val);
	}

	void start () {
		m_start_val = get_monotonic_time();
	}

	void update () {
		m_last_val = get_monotonic_time();
	}

	void reset () {
		m_start_val = m_last_val = 0;
	}

	uint64_t get_interval () {
		update ();
		if (valid()) {
			uint64_t elapsed = m_last_val - m_start_val;
			m_start_val = m_last_val;
			return elapsed;
		}
		return 0;
	}

	/// Elapsed time in microseconds
	uint64_t elapsed () const {
		if (!valid()) return 0;
		uint64_t elapsed = m_last_val - m_start_val;
		return elapsed;
	}

private:

	uint64_t m_start_val;
	uint64_t m_last_val;

};

class MOJO_API TimingData
{
public:
	TimingData () : m_reserve_size(256)
	{ reset (); }

	void start_timing () {
		m_timing.start ();
	}

	void add_elapsed () {
		m_timing.update ();
		if (m_timing.valid()) {
			m_elapsed_values.push_back (m_timing.elapsed());
		}
	}

	void add_interval () {
		uint64_t interval = m_timing.get_interval ();
		m_elapsed_values.push_back (interval);
	}

	void reset () {
		m_elapsed_values.clear ();
		m_elapsed_values.reserve (m_reserve_size);
	}

	std::string summary () const
	{ return timing_summary (m_elapsed_values); }

	bool get_min_max_avg_total (uint64_t& min,
	                            uint64_t& max,
	                            uint64_t& avg,
	                            uint64_t& total) const
	{ return mojo::get_min_max_avg_total (m_elapsed_values, min, max, avg, total); }

	void reserve (uint32_t reserve_size)
	{ m_reserve_size = reserve_size; reset (); }

	uint32_t size () const
	{ return m_elapsed_values.size(); }

private:

	Timing m_timing;

	uint32_t m_reserve_size;

	std::vector<uint64_t> m_elapsed_values;
};

class MOJO_API Timed
{
public:
	Timed (TimingData& data)
		: m_data(data)
	{
		m_data.start_timing ();
	}

	~Timed ()
	{
		m_data.add_elapsed ();
	}

private:

	TimingData& m_data;

};

} // namespace mojo

#endif // MOJO_CORE_TIMING_H
