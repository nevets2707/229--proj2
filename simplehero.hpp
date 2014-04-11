#include "Actor.hpp"
#include "Pos.hpp"

#ifndef __SIMPLE_H_
#define __SIMPLE_H_

class simplehero : public Actor
{

	private:
		int BFSearch(GraphMap* map, int x, int y, int g);
		Pos* findGoal(GraphMap* map, int x, int y);
		int reachOthers(GraphMap* map, int x, int y);	
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
