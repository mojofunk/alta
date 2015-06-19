#ifndef MOJO_ENGINE_EDGE_H
#define MOJO_ENGINE_EDGE_H

#ifndef MOJO_ENGINE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/engine/node.hpp"
#endif

namespace mojo {

class Edge {
public:
	Edge(const Node* from, const Node* to);

	void set_user_data(void*);

	void get_user_data(void*);

private:
	void* m_user_data;
};

} // namespace mojo

#endif // MOJO_ENGINE_EDGE_H
