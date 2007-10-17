#ifndef RTG_GRAPH_INCLUDED
#define RTG_GRAPH_INCLUDED

#include <set>

namespace rtg {

using std::set;

class Node;

// rtg_graph_t* rtg_graph_create (void);
// void rtg_graph_destroy (rtg_graph_t* graph);
// rtg_status_t rtg_graph_add_node (rtg_graph_t* graph, node_t* node);
// rtg_status_t rtg_graph_remove_node (rtg_graph_t* graph, node_t* node);
// rtg_status_t rtg_graph_connect_nodes (rtg_graph_t* graph, node_t* n1, node_t* n2);
// void rtg_graph_get_nodes (rtg_graph_t* graph, vector<node_t*> nodes);

class Graph
{
public:

	// Node* create_node(callback_func_t, void* user_data);
	// destroy_node(Node*);

	void insert (Node*);

	void erase (Node*);

	// size ()

	void connect (Node* n1, Node* n2);

	void disconnect (Node* n1, Node* n2);

	set<Node*> get_nodes () const;

private:

	set<Node*> m_nodes;

};

} // namespace rtg

#endif
