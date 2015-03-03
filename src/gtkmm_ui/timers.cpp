/*
    Copyright (C) 2014 Tim Mayberry

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include "timers.hpp"

#include "gleam/timer.hpp"

#include "mojo/core/debug.hpp"
#include "mojo/core/string/compose.hpp"

MOJO_DEBUG_DOMAIN(GUI_TIMING);

namespace {

class StandardTimer : public gleam::StandardTimer
{
public:
	StandardTimer (unsigned int interval)
		: gleam::StandardTimer(interval)
	{ }

	virtual bool on_elapsed () {
		MOJO_DEBUG_TIMING_ADD_ELAPSED(GUI_TIMING, timing_interval_data);
		MOJO_DEBUG_TIMING_START(GUI_TIMING, timing_exec_data);

		bool ret_val = gleam::StandardTimer::on_elapsed ();

		MOJO_DEBUG_TIMING_ADD_ELAPSED(GUI_TIMING, timing_exec_data);
		MOJO_DEBUG_TIMING_START(GUI_TIMING, timing_interval_data);
		return ret_val;
	}

#ifndef NDEBUG
	mojo::TimingData timing_interval_data;
	mojo::TimingData timing_exec_data;
#endif
};

class BlinkTimer : public gleam::BlinkTimer
{
public:
	BlinkTimer (unsigned int interval)
		: gleam::BlinkTimer(interval)
	{ }

	virtual bool on_elapsed () {
		MOJO_DEBUG_TIMING_ADD_ELAPSED(GUI_TIMING, timing_interval_data);
		MOJO_DEBUG_TIMING_START(GUI_TIMING, timing_exec_data);

		bool ret_val = gleam::BlinkTimer::on_elapsed ();

		MOJO_DEBUG_TIMING_ADD_ELAPSED(GUI_TIMING, timing_exec_data);
		MOJO_DEBUG_TIMING_START(GUI_TIMING, timing_interval_data);
		return ret_val;
	}

#ifndef NDEBUG
	mojo::TimingData timing_interval_data;
	mojo::TimingData timing_exec_data;
#endif
};


class UITimers
{
public:

	UITimers ()
		: blink(240)
		, slow(1000)
		, fast(100)
		, rapid(40)
	{
#ifndef NDEBUG
		slow.connect (sigc::mem_fun (*this, &UITimers::on_slow_timer));
#endif
	}

	BlinkTimer      blink;
	StandardTimer   slow;
	StandardTimer   fast;
	StandardTimer   rapid;

#ifndef NDEBUG
	std::vector<uint64_t> fast_eps_count;
	std::vector<uint64_t> rapid_eps_count;

private:

	void debug_fast_timer ()
	{
		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Fast Connections: %1\n",
				fast.connection_count ()));

		fast_eps_count.push_back (fast.timing_exec_data.size());

		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Fast Exec Totals: %1",
				mojo::timing_summary (fast_eps_count)));

		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Fast Interval: %1",
				fast.timing_interval_data.summary()));

		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Fast Exec: %1",
				fast.timing_exec_data.summary()));

		MOJO_DEBUG_TIMING_RESET(GUI_TIMING, fast.timing_interval_data);
		MOJO_DEBUG_TIMING_RESET(GUI_TIMING, fast.timing_exec_data);
	}

	void debug_rapid_timer ()
	{
		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Rapid Connections: %1\n",
				rapid.connection_count ()));

		rapid_eps_count.push_back (rapid.timing_exec_data.size());

		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Rapid Exec Totals: %1",
				mojo::timing_summary (rapid_eps_count)));

		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Rapid Interval: %1",
				rapid.timing_interval_data.summary()));

		MOJO_DEBUG_MSG(GUI_TIMING,
			mojo::compose ("Rapid Exec: %1",
				rapid.timing_exec_data.summary()));

		MOJO_DEBUG_TIMING_RESET(GUI_TIMING, rapid.timing_interval_data);
		MOJO_DEBUG_TIMING_RESET(GUI_TIMING, rapid.timing_exec_data);

	}

	void on_slow_timer () {
		debug_fast_timer ();
		debug_rapid_timer ();
	}
#endif
};

UITimers&
get_timers ()
{
	static UITimers timers;
	return timers;
}

} // anon namespace

namespace ui {

sigc::connection
slow_timer_connect (const sigc::slot<void>& slot)
{
	return get_timers().slow.connect (slot);
}

sigc::connection
fast_timer_connect (const sigc::slot<void>& slot)
{
	return get_timers().fast.connect (slot);
}

sigc::connection
rapid_connect (const sigc::slot<void>& slot)
{
	return get_timers().rapid.connect (slot);
}

sigc::connection
blink_connect (const sigc::slot<void,bool>& slot)
{
	return get_timers().blink.connect (slot);
}

} // namespace ui
