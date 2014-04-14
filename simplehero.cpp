#include <queue>
#include <set>
#include "Pos.hpp"
#include "simplehero.hpp"

simplehero::simplehero(int type) : Actor(type)
{
//	printf("Creating hero\n");
}

simplehero::~simplehero()
{
	
}

int simplehero::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{
	// printf("Selecting neighbor\n");
	int x, y, a, b;	
	Pos* goal = findGoal(map, cur_x, cur_y);
	int g;

	if(goal == 0)
	{
		printf("Couldn't find goal\n");
		return 0;
	}

	g = map->getVertex(goal->getX(), goal->getY());

	int toGo = BFSearch(map, cur_x, cur_y, g);
	
	//printf("Done searching\n");

	if(toGo == -1)
	{
	//	printf("No target found\n");
		delete goal;
		return 0;
	}
	
/*	if(p == 0 || p[1]->getX() < 0)
	{
		printf("ERRRORRORROR\n");
		goal = findGoal(map, cur_x, cur_y);
		toGo = BFSearch(map ,cur_x, cur_y, goal);
	}*/

	map->getPosition(toGo, x, y);
	
	
	for(int i = 0; i < map->getNumNeighbors(cur_x, cur_y); i++)
	{
		map->getNeighbor(cur_x, cur_y, i, a, b);
		if(x == a && y == b)
		{
			delete goal;

			return i;
		}
	}
	printf("Shouldn't get here");
	return 0;
}


int simplehero::BFSearch(GraphMap* map, int x, int y, int g)
{
	int a, b, curX, curY;
	int vert;
	std::queue<std::vector<int> > q;
	std::vector<int> first;	
	std::set<int> touched;
	int start = map->getVertex(x, y);
	first.push_back(start);
	q.push(first);
	touched.insert(start);

	if(start == g)
	{
		return start;
	}

	while(!q.empty())
	{
		std::vector<int> temp = q.front();
		q.pop();
		
		map->getPosition(temp.back(), curX, curY);
		for(int i = 0; i < map->getNumNeighbors(curX, curY); i++)
		{
			map->getNeighbor(curX, curY, i, a, b);
			vert = map->getVertex(a, b);
			if(!touched.count(vert))
			{
				std::vector<int> temp2 (temp);
				temp2.push_back(vert);
				touched.insert(vert);
				q.push(temp2);
				if(vert == g)
				{
					return temp2.at(1);
				}
			}
		}
	}
	return -1;
}

Pos* simplehero::findGoal(GraphMap* map, int x, int y)
{
	int a, b;
	Pos* goal;
	int goalX, goalY;
	int nX, nY;
	int goBack;

	for(int j = 0; j < map->getNumNeighbors(x, y); j++)
	{
		map->getNeighbor(x, y, j, nX, nY);
		for(int i = 0; i < map->getNumActors(); i++)
		{
			if(map->getActorType(i) & ACTOR_EATABLE)
			{
				if(map->getActorType(i) & ACTOR_DEAD)
				{
					continue;
				}
				map->getActorPosition(i, goalX, goalY);			
				if(goalX == nX && goalY == nY)
				{
					goal = new Pos(goalX, goalY);
					return goal;
				}
				
			}
		}
	}

	for(int i = 0; i < map->getNumActors(); i++)
	{
		if(map->getActorType(i) & ACTOR_EATABLE)
		{
			if(map->getActorType(i) & ACTOR_DEAD)
			{
				continue;
			}	
			map->getActorPosition(i, a, b);
			int v = map->getVertex(a,b);
			if(!BFSearch(map, x, y, v))
			{
				continue;
			}
			goal = new Pos(a, b);
			return goal;
		}
	}
	for(int i = 0; i < map->getNumActors(); i++)
	{
	
		if(map->getActorType(i) & 4)
		{
			if(map->getActorType(i) & ACTOR_DEAD)
			{
				continue;
			}

			map->getActorPosition(i, goalX, goalY);
			
		
			goBack = reachOthers(map, goalX, goalY);
			if(goBack == -1)
			{

				continue;
			}

			goal = new Pos(goalX, goalY);
			return goal;
		
		}
		
	}


	for(int i = 0; i <= map->getNumActors(); i++)
	{
		if(i == map->getNumActors())
		{
			return 0;
		}

		if(map->getActorType(i) & 4)
		{
			if(map->getActorType(i) & 16)
			{
				continue;
			}
			map->getActorPosition(i, goalX, goalY);
			if(goalX == -1 && goalY == -1)
			{
				continue;
			}
			break;	
		}
		
	}
	goal = new Pos(goalX, goalY);
	return goal;
}

int simplehero::reachOthers(GraphMap* map, int x, int y)
{
	int a, b;
	for(int i = 0; i < map->getNumActors(); i++)
	{
		if(map->getActorType(i) & ACTOR_EATABLE)
		{
			if(map->getActorType(i) & ACTOR_DEAD)
			{
				continue;
			}
			map->getActorPosition(i, a, b);
			if(x == a && y == b)
			{
				continue;
			}
			int v = map->getVertex(a, b);
			int s = BFSearch(map, x, y, v);
			if(s == -1)
			{
				return -1;
			}
		}
	}
	return 0;
}

Actor* simplehero::duplicate()
{ 
//	printf("Duplicating\n");
	simplehero* s = new simplehero(getType());
	return s;
}

const char* simplehero::getActorId()
{
//	printf("Getting id\n");
	return "simplehero";
}

const char* simplehero::getNetId()
{
	return "srmonson";
}
