#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_archive_modules
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/engine/engine.hpp"

using namespace boost::unit_test;
using namespace mojo;


BOOST_AUTO_TEST_CASE(test_engine_basic)
{
	Engine engine;

}

BOOST_AUTO_TEST_CASE(test_engine_graph)
{
	Engine engine;

	// an audio stream may be an aggregate stream that takes to async clocks
	// and resamples one of the streams but I think the engine should only have
	// one clock driving the process cycle.
	// engine.set_clock_source(test_clock_source);

	// The engine clock source may be 'ticking' but does that mean the state of
	// the engine depends on entirely on the clock source or can the engine be
	// started and stopped independently?

	// The audio driver will not always be the driver of the engine, for faster
	// than realtime processing/export a different clock source will be used.

	// what about other data sources with async clocks like midi drivers,
	// controllers etc. I guess all data should just be timestamped with the
	// clock source driving the engine and then the appropriate data

	// The engine runs async so we want all changes to be performed atomically
	// at the start or end of the engine process cycle.  So a copy of the
	// existing graph is made and changes are made to the copy and then the new
	// graph is set to be used on the next graph iteration.

	// Graph* graph = engine.get_graph();

	// The audio data from the audio stream will be copied into the ports of
	// the input bus at the start of the cycle but we should also be able to
	// test the graph by just writing data into the InputBus ports and test
	// that the data we have written has made it through the graph processing
	// and has arrived at the output bus ports

	// InputBus stereo_input_bus(DataType::Stereo);

	// graph.insert(stereo_input_bus);

	// StereoTrack stereo_track1;

	// graph.insert(stereo_track1.input_node());

	// graph.connect(stereo_input_bus, stereo_track1);

	// OutputBus stereo_output_bus(DataType::Stereo);

	// graph.insert(output_bus);

	// engine.set_graph(graph);

	// now iterate the clock source manually for a period of time, sleeping in
	// between.

	// test_clock_source.iterate();

	// test that the data has been processed by track and has made it to the
	// output bus ports
}
