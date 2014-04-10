#include <queue>
#include <set>
#include "SmartEnemy.hpp"
#include "Pos.hpp"


SmartEnemy::SmartEnemy(int type) : Actor(type)
{
}

SmartEnemy::~SmartEnemy()
{
}

int SmartEnemy::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{
	int x, y, a, b;
	Pos** p;
	Pos* goal = findGoal(map, cur_x, cur_y);
	
	for(int i = 0; i < map->getNumActors(); i++)
	{
		if(map->getActorType(i))
		{
			map->getActorPosition(i, x, y);
			if(x == cur_x && y == cur_y)
			{
				return 0;
			}
		}
	}

	if(goal == 0)
	{
		printf("Couldn't find goal\n");
		return 0;
	}


	Pos* toGo = BFSearch(map, cur_x, cur_y, goal);
	
	//printf("Done searching\n");

	if(toGo == 0)
	{
	//	printf("No target found\n");
		return 0;
	}
	
	p = toGo->getPath();
/*	if(p == 0 || p[1]->getX() < 0)
	{
		printf("ERRRORRORROR\n");
		goal = findGoal(map, cur_x, cur_y);
		toGo = BFSearch(map ,cur_x, cur_y, goal);
	}*/
	if(toGo->getPathSize() == 1)
	{
		return 0;
	}

		x = p[1]->getX();
		y = p[1]->getY();
	
	for(int i = 0; i < map->getNumNeighbors(cur_x, cur_y); i++)
	{
		map->getNeighbor(cur_x, cur_y, i, a, b);
		if(x == a && y == b)
		{
			return i;
		}
	}
	printf("Shouldn't get here");
	return 0;

}

Pos* SmartEnemy::BFSearch(GraphMap* map, int x, int y, Pos* g)
{
int a, b;
	int vert;
	Pos* temp;
	Pos* temp2;
	std::queue<Pos*> q;
	Pos* start = new Pos(x, y);
	start->setPathSize(0);
	start->makePath(0, 0);
	std::set<int> touched;

	if(start->equals(g))
	{
		return start;
	}

	q.push(start);
	vert = map->getVertex(start->getX(), start->getY());
	touched.insert(vert);

	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		for(int i = 0; i < map->getNumNeighbors(temp->getX(), temp->getY()); i++)
		{
			map->getNeighbor(temp->getX(), temp->getY(), i, a, b);
			temp2 = new Pos(a,b);
			vert = map->getVertex(a, b);
			if(!touched.count(vert))
			{
				temp2->setPathSize(temp->getPathSize());
				temp2->makePath(temp->getPathSize(), temp->getPath());
				q.push(temp2);
				touched.insert(vert);
			}
			if(temp2->equals(g))
			{
				return temp2;
			}
		}
	}

	return 0;

}

Pos* SmartEnemy::findGoal(GraphMap* map, int x, int y)
{
	//Find eatable and stand on it
	return 0;
}

Actor* SmartEnemy::duplicate()
{
	return new SmartEnemy(getType());
}

const char* SmartEnemy::getActorId()
{
	return "smartenemy";
}

const char* SmartEnemy::getNetId()
{
	return "srmonson";
}
