#include "Pos.hpp"
#include <stdlib.h>

//int x;
//int y;
//int pathSize;
//Pos** path;

Pos::Pos(int a, int b)
{
	path = 0;
	pathSize = 0;
	x = a;
	y = b;
}

Pos::~Pos()
{
	if(path != 0)
	{
		for(int i = 0; i < pathSize; i++)
		{
			delete path[i];

		}
		free(path);

	//	delete [] path;
	}

}

int Pos::getX()
{
	return x;
}

int Pos::getY()
{
	return y;
}

int Pos::getPathSize()
{
	return pathSize;
}	

Pos** Pos::getPath()
{
	return path;
}

void Pos::setPathSize(int oldSize)
{
	pathSize = (oldSize + 1);
}

void Pos::makePath(int oldSize, Pos** oldPath)
{
	Pos* cur = new Pos(x, y);
	path = (Pos**)malloc((oldSize + 1) * sizeof(Pos*)); //Not getting freed
//	path = Pos[oldSize + 1];

	for(int i = 0; i < oldSize; i++)
	{
		path[i] = oldPath[i];
	}
	path[oldSize] = new Pos(cur->getX(), cur->getY()); //Not getting freed
	delete cur;
}

bool Pos::operator==(Pos* other)
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

bool Pos::equals(Pos* other)
{
	if(x == other->getX())
	{
		if(y == other->getY())
		{
			return 1;
		}
	}
	return 0;
}