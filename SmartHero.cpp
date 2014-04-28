#include <queue>
#include <vector>
#include <set>
#include "SmartHero.hpp"

SmartHero::SmartHero(int type) : Actor(type)
{
}

SmartHero::~SmartHero()
{
}

int SmartHero::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{

	int x, y, a, b;

	int goal = findGoal(map, cur_x, cur_y);
	
	if(goal == -1)
	{
		return 0;
	}


	int toGo = BFSearch(map, cur_x, cur_y, goal);
	
	//printf("Done searching\n");

	if(toGo == -1)
	{
	//	printf("No target found\n");
		return 0;
	}

	map->getPosition(toGo, x, y);
	
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

int SmartHero::BFSearch(GraphMap* map, int x, int y, int g)
{
	
	int curX, curY;
	int tempX, tempY;
	int enemyX, enemyY;
	int dist, minDist;
	int vert;
	bool isEnemy;
	std::queue<std::vector<int> > q;
	std::queue<std::vector<int> > q2;
	std::set<int> touched;
	std::vector<int> temp;
	std::vector<int> start;
	start.push_back(map->getVertex(x, y));
	q.push(start);
		
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		map->getPosition(temp.back(), curX, curY);
		for(int i = 0; i < map->getNumNeighbors(curX, curY); i++)
		{
			isEnemy = false;
			minDist = -1;
			std::vector<int> temp2 (temp);
			map->getNeighbor(curX, curY, i, tempX, tempY);
			vert = map->getVertex(tempX, tempY);
			temp2.push_back(vert);
			if(vert == g)
			{
				return temp2.at(1);
			}
			for(int j = 0; j < map->getNumActors(); j++)
			{
				if(map->getActorType(j) & ACTOR_ENEMY)
				{
					map->getActorPosition(j, enemyX, enemyY);
					if(enemyX == tempX && enemyY == tempY)
					{
						isEnemy = true;
						break;
					}
					dist = (tempX - enemyX) * (tempX - enemyX) + (tempY - enemyY) * (tempY - enemyY);
					if(minDist == -1)
					{
						minDist = dist;
					}
					else if(dist < minDist)
					{
						minDist = dist;
					}

				}
			}
			if(!touched.count(vert) && !isEnemy)
			{
				if(minDist > 3 || minDist == -1)
				{
					q.push(temp2);
					touched.insert(vert);
				}
				else
				{
					q2.push(temp2);
				}
			}
		}
	}

	while(!q2.empty()) // may have probem with touched
	{
		temp = q2.front();
		q2.pop();

		map->getPosition(temp.back(), curX, curY);
		for(int i = 0; i < map->getNumNeighbors(curX, curY); i++)
		{
			map->getNeighbor(curX, curY, i, tempX, tempY);
			vert = map->getVertex(tempX, tempY);
			if(!touched.count(vert))
			{
				std::vector<int> temp2 (temp);
				temp2.push_back(vert);
				touched.insert(vert);
				if(vert == g)
				{
					return temp2.at(1);
				}
				for(int j = 0; j <= map->getNumActors(); j++)
				{
					if(j == map->getNumActors())
					{
						q2.push(temp2);
					}
					if(map->getActorType(j) & ACTOR_ENEMY)
					{
						map->getActorPosition(j, enemyX, enemyY);
						if(tempX == enemyX && tempY == enemyY)
						{
							break;
						}
					}
				}
			}
		}
	}
	return -1;
}

int SmartHero::findGoal(GraphMap* map, int x, int y)
{
	int temp, temp2;
	int curX, curY;
	int tempX, tempY;
	int enemyX, enemyY;
	int eatX, eatY;
	int dist;
	bool skip;
	std::queue<int> q;
	std::set<int> touched;
	std::vector<int> opt2;
	q.push(map->getVertex(x,y));
	dist = 0;

	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		map->getPosition(temp, curX, curY);
		dist++;
		for(int i = 0; i < map->getNumNeighbors(curX, curY); i++)
		{	
			map->getNeighbor(curX, curY, i, tempX, tempY);
			temp2 = map->getVertex(tempX, tempY);
			if(!touched.count(temp2))
			{
				for(int j = 0; j < map->getNumActors(); j++)
				{
					if(map->getActorType(j) & ACTOR_EATABLE)
					{
						if(map->getActorType(j) & ACTOR_DEAD)
						{
							continue;
						}

						map->getActorPosition(j, eatX, eatY);
						if(tempX == eatX && tempY == eatY)
						{
							int goal = map->getVertex(tempX, tempY);
							if(BFSearch(map, curX, curY, goal) == -1)
							{
								continue;
							}
							skip = false;
							for(int k = 0; k < map->getNumActors(); k++)
							{
								if(map->getActorType(k) & ACTOR_ENEMY)
								{
									map->getActorPosition(k, enemyX, enemyY);
									if((enemyX - tempX) * (enemyX - tempX) + (enemyY - tempY) * (enemyY - tempY) == 0)
									{
										return 0;
									}
									if((enemyX - tempX) * (enemyX - tempX) + (enemyY - tempY) * (enemyY - tempY) < dist)
									{
										opt2.push_back(goal);
										skip = true;
										break;
									}
								}
							}
							if(!skip)
							{
								return goal;
							}
						}
					}
				}
				touched.insert(temp2);
				q.push(temp2);
			}
		}
	}
	if(opt2.size() == 0)
	{
		return -1;
	}

	return opt2.at(0);
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
