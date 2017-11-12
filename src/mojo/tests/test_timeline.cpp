#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_timeline
#endif

#include "test_includes.hpp"

BOOST_AUTO_TEST_CASE(test_timeline)
{
	TimelinePosition invalid_pos;

	BOOST_CHECK_EQUAL(invalid_pos.valid(), false);

	TimelinePosition pos1(500, 1.0);

	BOOST_CHECK_EQUAL(pos1.sample, 500);
	BOOST_CHECK_EQUAL(pos1.qnote, 1.0);

	TimelinePosition pos1copy(pos1);

	BOOST_CHECK(pos1 == pos1copy);

	TimelinePosition pos2(2000, 3.0);

	BOOST_CHECK_EQUAL(pos2.sample, 2000);
	BOOST_CHECK_EQUAL(pos2.qnote, 3.0);

	TimelineDuration duration1;

	BOOST_CHECK_EQUAL(duration1.valid(), false);

	TimelineDuration duration2 = pos2 - pos1;

	BOOST_CHECK_EQUAL(duration2.samples, pos2.sample - pos1.sample);
	BOOST_CHECK_EQUAL(duration2.qnotes, pos2.qnote - pos1.qnote);

	BOOST_CHECK_EQUAL(duration2.valid(), true);

	TimelinePosition pos3 = pos1 + duration2;

	BOOST_CHECK_EQUAL(pos3.sample, pos2.sample);
	BOOST_CHECK_EQUAL(pos3.qnote, pos2.qnote);
	BOOST_CHECK(pos3 == pos2);

	BOOST_CHECK(duration2 == duration_between(pos1, pos2));
	BOOST_CHECK(duration2 == duration_between(pos2, pos1));
}
