void Graph::insert(Node* node)
{
	m_nodes.insert(node);
}

void Graph::erase(Node* node)
{
	m_nodes.erase(node);
}

void Graph::connect(Node* n1, Node* n2)
{
	// add an outgoing edge to n1 to n2
	// add an incoming edge to n2 from n2
}

void Graph::disconnect(Node* n1, Node* n2)
{
}

std::set<Node*> Graph::get_nodes() const
{
	return m_nodes;
}

void Graph::reset_processing()
{
}

void Graph::iterate() const
{
}
