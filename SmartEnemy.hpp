#ifndef __ENEMY_H_
#define __ENEMY_H_

#include "Pos.hpp"
#include "Actor.hpp"


class SmartEnemy : public Actor
{
	private:
		Pos* BFSearch(GraphMap* map, int x, int y, Pos* g);
		Pos* findGoal(GraphMap* map, int x, int y);

	public:
		SmartEnemy(int type);
		virtual ~SmartEnemy();
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
		virtual int selectNeighbor(GraphMap* map, int cur_x, int cur_y);

};

#endif
