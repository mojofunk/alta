#ifndef MOJO_CORE_TIMELINE_H
#define MOJO_CORE_TIMELINE_H

typedef int64_t sample_t;

typedef double qnote_t;

// not used ATM
enum TimelineUnit {
	Samples,     // Sample value is the valid reference unit
	QuarterNotes // QuarterNotes value is the valid reference unit
};

/*
 * A duration is not connected to the timeline in that it does not have
 * a position, it is just a measurement of elapsed time or offset.
 *
 * In saying that, a TimelineDuration is only valid between two
 * TimelinePositions. You can't add create a TimelineDuration and add it
 * to any TimelinePosition and expect the TimelinePosition to be valid.
 */
class TimelineDuration
{
public: // member variables
	const sample_t samples;
	const qnote_t qnotes;

public: // ctors
	// Create a duration with all valid values
	TimelineDuration(sample_t p_samples, qnote_t p_qnotes)
	    : samples(p_samples)
	    , qnotes(p_qnotes)
	{
	}

	// Create invalid duration
	TimelineDuration()
		: samples(0)
		, qnotes(std::numeric_limits<qnote_t>::infinity())
	{}

	TimelineDuration(const TimelineDuration&) = default;

public: // operators
	TimelineDuration& operator=(const TimelineDuration&) = default;

	bool operator==(const TimelineDuration& other) const
	{
		assert (valid());
		return samples == other.samples && qnotes == other.qnotes;
	}

	bool operator!=(const TimelineDuration& other) const
	{
		return !(*this == other);
	}

public: // methods
	bool valid() const
	{
		return qnotes != std::numeric_limits<qnote_t>::infinity();
	}

public: // static constants

	static TimelineDuration min() {
		return TimelineDuration(1, std::numeric_limits<qnote_t>::min());
	}

	static TimelineDuration max() {
		return TimelineDuration(std::numeric_limits<sample_t>::max(),
		                        std::numeric_limits<qnote_t>::max());
	}

};

/*
 * An instantaneous point on the timeline at which all timeline units
 * contained in the TimelinePosition are valid.
*/
class TimelinePosition
{
public: // member variables
	sample_t sample;
	qnote_t qnote;

public: // ctors
	// All values are valid
	TimelinePosition(sample_t p_sample, qnote_t p_qnote)
	    : sample(p_sample)
	    , qnote(p_qnote)
	{
	 assert (sample >= 0);
	 assert (qnote >= 0.0);
	}

	// All values are invalid
	TimelinePosition()
	    : sample(0)
	    , qnote(std::numeric_limits<qnote_t>::infinity())
	{
	}

	TimelinePosition(const TimelinePosition&) = default;

public: // methods
	bool valid() const
	{
		return qnote != std::numeric_limits<qnote_t>::infinity();
	}

public: // operators

	TimelinePosition& operator=(const TimelinePosition&) = default;

	bool operator==(const TimelinePosition& other) const
	{
		assert (valid());
		return sample == other.sample && qnote == other.qnote;
	}

	bool operator!=(const TimelinePosition& other) const
	{
		return !(*this == other);
	}

	// get the duration between two TimelinePositions
	TimelineDuration operator-(const TimelinePosition& pos) const
	{
		assert (pos < *this);
		return TimelineDuration(sample - pos.sample, qnote - pos.qnote);
	}

	TimelinePosition operator+(const TimelineDuration& duration) const
	{
		assert (valid() && duration.valid());
		return TimelinePosition (sample + duration.samples, qnote + duration.qnotes);
	}

	TimelinePosition operator-(const TimelineDuration& duration) const
	{
		assert (valid() && duration.valid());
		return TimelinePosition (sample - duration.samples, qnote - duration.qnotes);
	}

	/*
	 * For the comparison operators only a single unit is needed for
	 * comparison as the invariant is that all units are valid and that if
	 * for instance pos1.sample > pos2.sample then the same is true for
	 * all other values.
	 */

	bool operator>(const TimelinePosition& other) const
	{
		assert (valid());
		return sample > other.sample;
	}

	bool operator<(const TimelinePosition& other) const
	{
		assert (valid());
		return sample < other.sample;
	}

	bool operator>=(const TimelinePosition& other) const
	{
		assert (valid());
		return sample >= other.sample;
	}

	bool operator<=(const TimelinePosition& other) const
	{
		assert (valid());
		return sample <= other.sample;
	}

public: // static constants
	static TimelinePosition min() { return TimelinePosition(0, 0.0); }

	static TimelinePosition max()
	{
		return TimelinePosition(std::numeric_limits<sample_t>::max(),
		                        std::numeric_limits<qnote_t>::max());
	}
};

static TimelineDuration duration_between(const TimelinePosition& pos1,
                                         const TimelinePosition& pos2)
{
	if (pos1 > pos2) {
		return pos1 - pos2;
	}
	return pos2 - pos1;
}

/*
 * A period of time on the timeline with a start position, end position and
 * duration.
 *
 * Could also be called TimelinePeriod or TimelineSection.
 */
class TimelineRange
{
public:
	const TimelinePosition start;
	const TimelinePosition end;

public: // ctors
	TimelineRange(const TimelinePosition& start, const TimelinePosition& end)
	    : start(start)
	    , end(end)
	{
		//assert (end > start);
	}

	// Allow creation of invalid Range ?
	TimelineRange() = delete;

	TimelineRange(const TimelineRange&) = default;

public:
	TimelineDuration duration() const
	{
		return end - start;
	}

	bool operator==(const TimelineRange& other) const
	{
		return start == other.start && end == other.end;
	}
};

#endif // MOJO_CORE_TIMELINE_H
