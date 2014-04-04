

SmartHero::SmartHero(int type) : Actor(type)
{
}

SmartHero::~SmartHero()
{
}

int SmartHero::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{
	return 0;
}

Pos* BFSearch(GraphMap* map, int x, int y, Pos* g)
{
	return 0;
}

Pos* findGoal(GraphMap* map, int x, int y)
{
	return 0;
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
