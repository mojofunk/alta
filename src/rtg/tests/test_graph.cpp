
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <rtg/graph.hpp>
#include <rtg/node.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace rtg;

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



}

void
test_graph_api()
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

test_suite*
init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* test = BOOST_TEST_SUITE( "rtg::Graph" );

	test->add( BOOST_TEST_CASE( &test_graph_api ) );

	return test;
}
