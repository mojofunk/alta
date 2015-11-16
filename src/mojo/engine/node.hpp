#ifndef MOJO_NODE_H
#define MOJO_NODE_H

namespace mojo {

class Node {
public:
	/**
	 * @return true if Node has any output ports/outgoing edges.
	 */
	bool is_source() const;

	/**
	 * @return true if Node has any input ports/incoming edges.
	 */
	bool is_sink() const;

	void add_outgoing_edge(Node* sink);

	std::set<Node*> outgoing_edges() const;

	// vector<Node*> incoming_edges () const;

protected:
	virtual ~Node() {}

	virtual void on_activate() = 0;

private:
	std::set<Node*> m_in_edges;
	std::set<Node*> m_out_edges;
};

} // namespace mojo

#endif // MOJO_NODE_H
