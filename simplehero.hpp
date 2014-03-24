#include "Actor.hpp"

#ifndef __SIMPLE_H_
#define __SIMPLE_H_

class simplehero : public Actor
{

	private:
		void BFSearch(GraphMap* map, int x, int y);
	protected:

	public:
		int selectNeighbor(GraphMap* map, int cur_x, int cur_y);

};

#endif
