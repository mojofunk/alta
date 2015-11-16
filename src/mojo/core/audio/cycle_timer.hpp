#ifndef MOJO_AUDIO_CYCLE_TIMER_H
#define MOJO_AUDIO_CYCLE_TIMER_H

namespace mojo {

class CycleTimer {
public:
	CycleTimer()
	    : m_cycle_start(0)
	    , m_samplerate(0)
	    , m_samples_per_cycle(0)
	{
	}

	void set_samplerate(double samplerate) { m_samplerate = samplerate; }

	double get_samplerate() const { return m_samplerate; }

	double get_sample_length_us() const { return 1e6 / m_samplerate; }

	double get_length_us() const
	{
		return get_sample_length_us() * m_samples_per_cycle;
	}

	void set_samples_per_cycle(uint32_t samples) { m_samples_per_cycle = samples; }

	uint32_t get_samples_per_cycle() const { return m_samples_per_cycle; }

	// rint?? that may round to sample outside of cycle?
	// max(0, value)?
	uint32_t samples_since_cycle_start(uint64_t timer_val) const
	{
		if (timer_val < m_cycle_start) {
			return 0;
		}
		return std::max((double)0,
		                (timer_val - get_start()) / get_sample_length_us());
	}

	uint64_t timestamp_from_sample_offset(uint32_t sample_offset)
	{
		return m_cycle_start + get_sample_length_us() * sample_offset;
	}

	bool valid() const { return m_samples_per_cycle && m_samplerate; }

	bool in_cycle(uint64_t timer_value_us) const
	{
		return (timer_value_us >= get_start()) && (timer_value_us < get_next_start());
	}

	void reset_start(uint64_t timestamp) { m_cycle_start = timestamp; }

	uint64_t get_start() const { return m_cycle_start; }

	uint64_t microseconds_since_start(uint64_t timestamp) const
	{
		return timestamp - m_cycle_start;
	}

	uint64_t microseconds_since_start(uint32_t samples) const
	{
		return m_cycle_start + samples * get_sample_length_us();
	}

	uint64_t get_next_start() const
	{
		return m_cycle_start + rint(get_length_us());
	}

private:
	uint64_t m_cycle_start;

	uint32_t m_samplerate;
	uint32_t m_samples_per_cycle;
};

} // namespace mojo

#endif // MOJO_AUDIO_CYCLE_TIMER_H
