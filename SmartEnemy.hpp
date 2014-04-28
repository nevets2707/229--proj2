#ifndef __ENEMY_H_
#define __ENEMY_H_

#include "Actor.hpp"
#include <vector>

class SmartEnemy : public Actor
{
	private:
		int opt;
		std::vector<SmartEnemy*> list;
		int BFSearch(GraphMap* map, int x, int y, int g);
		int findGoal(GraphMap* map, int x, int y);
		int findGoalOpt2(GraphMap* map, int x, int y);

	public:
		SmartEnemy(int type);
		virtual ~SmartEnemy();
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
		virtual int selectNeighbor(GraphMap* map, int cur_x, int cur_y);

};

#endif
