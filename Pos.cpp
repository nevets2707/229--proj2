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
		delete [] path;
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

int* Pos::getPath()
{
	return path;
}

void Pos::setPathSize(int oldSize)
{
	pathSize = (oldSize + 1);
}

void Pos::makePath(int oldSize, int* oldPath, int cur)
{
	path = new int[oldSize + 1];
	for(int i = 0; i < oldSize; i++)
	{
		path[i] = oldPath[i];
	}
	path[oldSize] = cur;
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
