#include "Pos.hpp"

int x;
int y;

Pos::Pos(int a, int b)
{
	x = a;
	y = b;
}

Pos::~Pos()
{

}

int Pos::getX()
{
	return x;
}

int Pos::getY()
{
	return y;
}

bool Pos::equal(Pos* other)
{
	if(x == other->getX())
	{
		if(y == other->getY())
		{
			return true;
		}
	}
	return false;
}
