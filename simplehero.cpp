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
	Pos** p;
	Pos* goal = findGoal(map, cur_x, cur_y);
	
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
		delete goal;
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
		
		delete goal;
		for(int i = 0; i < toGo->getPathSize(); i++)
		{
			delete p[i];
		}
	//	delete toGo;
		return 0;
	}

	x = p[1]->getX();
	y = p[1]->getY();
	
	for(int i = 0; i < map->getNumNeighbors(cur_x, cur_y); i++)
	{
		map->getNeighbor(cur_x, cur_y, i, a, b);
		if(x == a && y == b)
		{
			delete goal;
			for(int j = 0; j < toGo->getPathSize(); j++)
			{
				delete p[j];
			}
	//		delete toGo;
			return i;
		}
	}
	printf("Shouldn't get here");
	return 0;
}


Pos* simplehero::BFSearch(GraphMap* map, int x, int y, Pos* g)
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
	start->makePath(0, 0);
	std::set<int> touched;

	if(start->equals(g))
	{
		return start;
	}

	q.push(start);
	vert = map->getVertex(start->getX(), start->getY());
	touched.insert(vert);

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
				temp2->makePath(temp->getPathSize(), temp->getPath());
				q.push(temp2);
				touched.insert(vert);
			}
			if(temp2->equals(g))
			{
				//delete start;
				std::swap(q,empty);
				return temp2;
			}
			//delete temp2;
		}
	}

	delete start;
	return 0;
}

Pos* simplehero::findGoal(GraphMap* map, int x, int y)
{

	Pos* goal;
	int goalX, goalY;
	bool skipped = false;
	Pos* cur = new Pos(x, y);
	Pos* goBack = 0;
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
			
			goBack = BFSearch(map, goalX, goalY, cur);
			if(goBack == 0)
			{
				skipped = true;
				continue;
			}

			goal = new Pos(goalX, goalY);
			delete cur;
			delete goBack;
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
	delete cur;
	delete goBack;
	return goal;
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
