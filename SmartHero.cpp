#include <queue>
#include <set>
#include "SmartHero.hpp"
#include "Pos.hpp"

SmartHero::SmartHero(int type) : Actor(type)
{
}

SmartHero::~SmartHero()
{
}

int SmartHero::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{
/*	int x, y, a, b;
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
		return 0;
	}
	
	p = toGo->getPath();

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
*/
}

Pos* SmartHero::BFSearch(GraphMap* map, int x, int y, Pos* g)
{
/*	int a, b;
	int enemyX, enemyY;
	int vert;
	bool skip;
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
			skip = false;
			if(!touched.count(vert))
			{
				for(int i = 0; i < map->getNumActors(); i++)
				{
					if(map->getActorType(i) & ACTOR_ENEMY)
					{
						map->getActorPosition(i, enemyX, enemyY);
						if(a == enemyX && b == enemyY)
						{
							touched.insert(vert);
							skip = true;
						}
					}
				}
				if(skip)
				{
					continue;
				}
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
*/
}

Pos* SmartHero::findGoal(GraphMap* map, int x, int y)
{
/*	Pos* goal;
	int goalX, goalY;
	bool skipped = false;
	Pos* cur = new Pos(x, y);
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
			if(map->getActorType(i) & 16)
			{
				continue;
			}
			map->getActorPosition(i, goalX, goalY);
			if(goalX == -1 && goalY == -1)
			{
				continue;
			}
			if(!BFSearch(map, goalX, goalY, cur))
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
*/
}

Actor* SmartHero::duplicate()
{
	return new SmartHero(getType());
}

const char* SmartHero::getActorId()
{
	return "smarthero";
}

const char* SmartHero::getNetId()
{
	return "srmonson";
}
