#ifndef MOJO_ENGINE_EDGE_H
#define MOJO_ENGINE_EDGE_H

/**
 * Use the name Edge rather than Connection as we may want to use that
 * identifier in another context.
 */
class Edge
{
public:
	Edge(const Node* from, const Node* to);

	void set_user_data(void*);

	void get_user_data(void*);

private:
	void* m_user_data;
};

#endif // MOJO_ENGINE_EDGE_H
