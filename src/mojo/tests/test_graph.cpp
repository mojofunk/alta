#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_graph
#endif

#include "test_includes.hpp"

#include "mojo-engine.hpp"

struct Processor : public Node {
	string name;

protected:
	virtual void on_activate() { BOOST_TEST_MESSAGE(name); }
};

bool
graph_contains_node(Node*)
{
	return true;
}

BOOST_AUTO_TEST_CASE(test_graph_application)
{
	Graph g;

	Processor* p1 = new Processor;
	Processor* p2 = new Processor;

	p1->name = "P1";
	p2->name = "P2";

	g.insert(p1);
	g.insert(p2);

	// check nodes have been added to the graph

	g.connect(p1, p2);
}
