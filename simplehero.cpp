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
	//printf("Breath-First Searching\n");
	int a, b;
	int vert;
	Pos* temp;
	Pos* temp2;
	std::queue<Pos*> q;
	std::queue<Pos*> empty;
	Pos* start = new Pos(x, y);  //Not getting freed
	start->setPathSize(0);
	start->makePath(0,0,g);
	std::set<int> touched;

	q.push(start);
	vert = map->getVertex(start->getX(), start->getY());
	touched.insert(vert);

	if(vert == g)
	{
		delete start;
		return vert;
	}
	//delete start;

	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		for(int i = 0; i < map->getNumNeighbors(temp->getX(), temp->getY()); i++)
		{
			map->getNeighbor(temp->getX(), temp->getY(), i, a, b);
			temp2 = new Pos(a,b);  //Not getting freed
			vert = map->getVertex(a, b);
			if(!touched.count(vert))
			{
				temp2->setPathSize(temp->getPathSize());
				temp2->makePath(temp->getPathSize(), temp->getPath(), vert);
				q.push(temp2);
				touched.insert(vert);
			}
			if(vert == g)
			{
				//delete start;
				int x = temp2->getPath()[1];
				while(!q.empty())
				{
					Pos* p = q.front();
					q.pop();
					delete p;
				}
		//		delete temp2;
				delete start;
				return x;
			}
			//delete temp2;
		}
	}
	delete temp2;
	delete start;
	return -1;
}

Pos* simplehero::findGoal(GraphMap* map, int x, int y)
{

	Pos* goal;
	int goalX, goalY;
	int nX, nY;
	bool skipped = false;	
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
	for(int i = 0; i <= map->getNumActors(); i++)
	{
		if(i == map->getNumActors())
		{
			if(skipped)
			{
				continue;
			}
			return 0;
		}

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
				skipped = true;
				continue;
			}

			goal = new Pos(goalX, goalY);
			return goal;
		
		}
		
	}

	if(skipped)
	{
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
	}

//	printf("Going for (%d,%d)\n", goalX, goalY);
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
