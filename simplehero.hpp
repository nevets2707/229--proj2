#include "Actor.hpp"
#include "Pos.hpp"

#ifndef __SIMPLE_H_
#define __SIMPLE_H_

class simplehero : public Actor
{

	private:
		Pos* BFSearch(GraphMap* map, int x, int y, Pos* g);
		Pos* findGoal(GraphMap* map, int time);
		int time;
	protected:

	public:
		simplehero(int type);
		virtual ~simplehero();
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual int selectNeighbor(GraphMap* map, int cur_x, int cur_y);
		virtual const char* getNetId();

};

#endif
