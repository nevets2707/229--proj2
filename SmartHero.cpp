#include <queue>
#include <vector>
#include <set>
#include "SmartHero.hpp"
#include "Node.hpp"

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
		printf("Couldn't find goal\n");
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
	int a, b;
	int enemyX, enemyY;
	int vert;
	std::vector<int> temp;
	bool skip;
	int count = 0;
	int start = map->getVertex(x, y);

	std::priority_queue<Node> q;

	std::set<int> touched;

	if(start == g)
	{
		return start;
	}
	Node first(count, std::vector<int> a, start);
	q.push(first);
	touched.insert(start);

	while(!q.empty())
	{
		count++;
		Node temp = q.top();
		q.pop();
		int curX, curY;
		map->getPosition(temp.getPath().back(), curX, curY);
		for(int i = 0; i < map->getNumNeighbors(curX, curY); i++)
		{
			map->getNeighbor(curX, curY, i, a, b);
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

				Node temp2 = new Node(count, temp.getPath(), vert);
				q.push(temp2);
				touched.insert(vert);
			}
			if(vert == g)
			{
				return temp.getPath().at(1);
			}
		}
	}

	return -1;

}

int SmartHero::findGoal(GraphMap* map, int x, int y)
{
	int goal;
	int goalX, goalY;
	bool skipped = false;
	int cur = map->getVertex(x, y);
	for(int i = 0; i <= map->getNumActors(); i++)
	{
		if(i == map->getNumActors())
		{
			if(skipped)
			{
				continue;
			}
			return -1;
		}

		if(map->getActorType(i) & ACTOR_EATABLE)
		{
			if(map->getActorType(i) & ACTOR_DEAD)
			{
				continue;
			}
			map->getActorPosition(i, goalX, goalY);
			if(!BFSearch(map, goalX, goalY, cur))
			{
				skipped = true;
				continue;
			}
			goal = map->getVertex(goalX, goalY);
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

			if(map->getActorType(i) & ACTOR_EATABLE)
			{
				if(map->getActorType(i) & ACTOR_DEAD)
				{
					continue;
				}
				map->getActorPosition(i, goalX, goalY);
				break;	
			}
			
		}
	}

//	printf("Going for (%d,%d)\n", goalX, goalY);
	goal = map->getVertex(goalX, goalY);
	return goal;

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
