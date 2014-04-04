#ifndef __SMART_H_
#define __SMART_H_

class SmartHero : public Actor
{
	private:
		Pos* BFSearch(Graphmap* map, int x, int y, Pos* g);
		Pos* findGoal(Graphmap* map, int x, int y);

	public:
		SmartHero(int type);
		virtual ~SmartHero();
		virtual Actor* duplicate();
		virtual const char* getActorId();
		virtual int selectNeighbor(Graphmap* map, int cur_x, int cur_y);
		virtual const char* getNetId();

};


#endif
