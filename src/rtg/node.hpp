#ifndef RTG_NODE_INCLUDED
#define RTG_NODE_INCLUDED

#include <set>

namespace rtg {

using std::set;

class Node {
public:

	bool is_source () const;

	bool is_sink () const;

	void add_outgoing_edge (Node* sink);

	set<Node*> outgoing_edges () const;

	//vector<Node*> incoming_edges () const;

protected:
	
	virtual ~Node() { }

	virtual void on_activate () = 0;

private:

	set<Node*> m_in_edges;
	set<Node*> m_out_edges;

};

} // namespace rtg

#endif
