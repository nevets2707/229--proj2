#ifndef __POWERUP_H_
#define __POWERUP_H_

#include "Actor.hpp"
#include "Pos.hpp"

class SmartPowerup : public Actor
{
	private:
		Pos* BFSearch(GraphMap* map, int x, int y, Pos* g);
		Pos* findGoal(GraphMap* map, int x, int y);

	public:
		SmartPowerup(int type);
		virtual ~SmartPowerup();
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual const char* getNetId();
		virtual int selectNeighbor(GraphMap* map, int cur_x, int cur_y);
};

#endif
