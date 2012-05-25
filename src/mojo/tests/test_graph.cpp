#define BOOST_TEST_MODULE graph

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/engine/graph.hpp"
#include "mojo/engine/node.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

struct Processor : public Node
{
	string name;

protected:

	virtual void on_activate()
	{
		BOOST_MESSAGE(name);
	}

};

bool
graph_contains_node (Node*)
{


	return true;
}

BOOST_AUTO_TEST_CASE( test_graph_api )
{
	Graph g;
	
	Processor* p1 = new Processor;
	Processor* p2 = new Processor;

	p1->name = "P1";
	p2->name = "P2";

	g.insert(p1);
	g.insert(p2);

	// check nodes have been added to the graph

	g.connect(p1,p2);

}
