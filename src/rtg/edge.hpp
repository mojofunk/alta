#ifndef RTG_GRAPH_INCLUDED
#define RTG_GRAPH_INCLUDED

namespace rtg {

class Node;

class Edge {
public:

	Edge (const Node* from, const Node* to);

	void set_user_data (void*);

	void get_user_data (void*);

private:

	void* m_user_data;

}

} // namespace rtg

#endif
