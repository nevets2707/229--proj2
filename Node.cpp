#include "Node.hpp"
#include <vector>
Node::Node(int w, std::vector<int> p, int add)
{
	weight = w;
	path (p);
	path.push_back(add);
}

Node::~Node()
{

}


Node::getWeight()
{
	return weight;
}

Node::getPath()
{
	return path;
}

Node::operator<(const Node& other)
{
	return weight > other.getWeight();
}
