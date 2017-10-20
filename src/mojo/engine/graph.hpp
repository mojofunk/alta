#ifndef MOJO_GRAPH_H
#define MOJO_GRAPH_H

class Node;

/**
 * A Graph can be made up of many disconnected directed acyclic graph's(DAG)
 * where each DAG can be processed by a number of threads.
 */
class Graph
{
public:
	// Node* create_node(callback_func_t, void* user_data);
	// destroy_node(Node*);

	void insert(Node*);

	void erase(Node*);

	// size ()

	void connect(Node* n1, Node* n2);

	void disconnect(Node* n1, Node* n2);

	std::set<Node*> get_nodes() const;

	/**
	 * Called at the start of the processing cycle before any calls to iterate
	 * to reset the graph for processing.
	 */
	void reset_processing();

	/**
	 * iterate is called to process the graph. It can be called by many
	 * threads. If graph processing has finished and each node in the graph has
	 * been marked as processed then iterate will return.
	 */
	void iterate() const;

private:
	std::set<Node*> m_nodes;
};

#endif // MOJO_GRAPH_H
