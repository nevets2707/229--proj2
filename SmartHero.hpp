#include "Pos.hpp"
#include "Actor.hpp"

#ifndef __SMART_H_
#define __SMART_H_

class SmartHero : public Actor
{
	private:
		int BFSearch(GraphMap* map, int x, int y, int g);
		int findGoal(GraphMap* map, int x, int y);

	public:
		SmartHero(int type);
		virtual ~SmartHero();
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual int selectNeighbor(GraphMap* map, int cur_x, int cur_y);
		virtual const char* getNetId();

};

#endif
