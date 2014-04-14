#include <vector>

class Node
{

	private:
		int weight;
		std::vector<int> path;

	public:
		Node(int w, std::vector<int> p, int add);
		~Node;
		std::vector<int> getPath();
		int getWeight();
		int operator<(const Node& other);
};
