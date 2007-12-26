#ifndef MOJO_GRAPH_INCLUDED
#define MOJO_GRAPH_INCLUDED

#include <set>

namespace mojo {

using std::set;

class Node;

// mojo_graph_t* mojo_graph_create (void);
// void mojo_graph_destroy (mojo_graph_t* graph);
// mojo_status_t mojo_graph_add_node (mojo_graph_t* graph, node_t* node);
// mojo_status_t mojo_graph_remove_node (mojo_graph_t* graph, node_t* node);
// mojo_status_t mojo_graph_connect_nodes (mojo_graph_t* graph, node_t* n1, node_t* n2);
// void mojo_graph_get_nodes (mojo_graph_t* graph, vector<node_t*> nodes);

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

} // namespace mojo

#endif
