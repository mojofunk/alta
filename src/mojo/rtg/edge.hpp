#ifndef MOJO_GRAPH
#define MOJO_GRAPH

namespace mojo {

class Node;

class Edge {
public:

	Edge (const Node* from, const Node* to);

	void set_user_data (void*);

	void get_user_data (void*);

private:

	void* m_user_data;

}

} // namespace mojo

#endif
