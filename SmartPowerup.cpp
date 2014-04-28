#include <queue>
#include <set>
#include "SmartPowerup.hpp"

SmartPowerup::SmartPowerup(int type) : Actor(type)
{

}

SmartPowerup::~SmartPowerup()
{
}

int SmartPowerup::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{
	int a, b;
	int goal;
	int actorPair;
	actorPair = findGoal(map, cur_x, cur_y);
	if(actorPair == -1)
	{
		return 0;
	}	
	
	map->getActorPosition(actorPair, a, b);	
	goal = map->getVertex(a, b);	
	
	int goTo = BFSearch(map, cur_x, cur_y, goal);

	if(goTo == -1)
	{
		return 0;
	}
	
	for(int i = 0; i < map->getNumNeighbors(cur_x, cur_y); i++)
	{
		map->getNeighbor(cur_x, cur_y, i, a, b);
		int v = map->getVertex(a,b);
		if(goTo == v)
		{
			return i;
		}
	}
	
	return 0;
}

int SmartPowerup::BFSearch(GraphMap* map, int x, int y, int g)
{
	int a, b, curX, curY;
	int heroX, heroY;
	int vert;
	bool badPath;
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
			badPath = false;
			map->getNeighbor(curX, curY, i, a, b);
			vert = map->getVertex(a, b);
			if(!touched.count(vert))
			{
				std::vector<int> temp2 (temp);
				temp2.push_back(vert);
				touched.insert(vert);
				for(int j = 0; j < map->getNumActors(); j++)
				{
					if(map->getActorType(j) & ACTOR_HERO)
					{
						map->getActorPosition(j, heroX, heroY);
						if(vert == map->getVertex(heroX, heroY))
						{
							badPath = true;
						}
					}
				}
				if(!badPath)
				{
					q.push(temp2);
				}
				if(vert == g)
				{
					return temp2.at(1);
				}
			}
		}
	}
	return -1;
}	

int SmartPowerup::findGoal(GraphMap* map, int x, int y)
{	
	int temp, tempX, tempY;
	int temp2;
	int enemyX, enemyY;
	int a, b;
	std::queue<int> q;
	std::set<int> touched;
	q.push(map->getVertex(x,y));
	
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		map->getPosition(temp, tempX, tempY);
		for(int i = 0; i < map->getNumNeighbors(tempX, tempY); i++)
		{
			map->getNeighbor(tempX, tempY, i, a, b);
			temp2 = map->getVertex(a, b);
			if(!touched.count(temp2))
			{
				for(int j = 0; j < map->getNumActors(); j++)
				{
					if(map->getActorType(j) & ACTOR_ENEMY)
					{
						map->getActorPosition(j, enemyX, enemyY);
						if(a == enemyX && b == enemyY)
						{
							return j;
						}
					}
				}
				touched.insert(temp2);
				q.push(temp2);
			}
		}
	}

	return -1;
}

Actor* SmartPowerup::duplicate()
{
	return new SmartPowerup(getType());
}

const char* SmartPowerup::getActorId()
{
	return "smartpowerup";
}

const char* SmartPowerup::getNetId()
{
	return "srmonson";
}
