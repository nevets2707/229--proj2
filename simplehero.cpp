#include <queue>
#include <set>
#include "Pos.hpp"
#include "simplehero.hpp"



int simplehero::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{


	return -111;	
}


void simplehero::BFSearch(GraphMap* map, int x, int y)
{
	int a, b;
	Pos* temp;
	Pos* temp2;
	std::queue<Pos*> q;
	Pos* start = new Pos(x, y);
	std::set<Pos*> touched;

	q.push(start);
	touched.insert(start);

	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		for(int i = 0; i < map->getNumNeighbors(temp->getX(), temp->getY()); i++)
		{
			map->getNeighbor(temp->getX(), temp->getY(), i, a, b);
			temp2 = new Pos(a,b);
			if(!touched.count(temp2))
			{
				q.push(temp2);
				touched.insert(temp2);
			}
		}
	}
}
