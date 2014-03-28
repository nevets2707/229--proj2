#include "Pos.hpp"
#include <stdlib.h>

int x;
int y;
int pathSize;
Pos** path;

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

	path = (Pos**)malloc((oldSize + 1) * sizeof(Pos*));
	for(int i = 0; i < oldSize; i++)
	{
		path[i] = (Pos*)malloc(sizeof(Pos));
		path[i] = oldPath[i];
	}
	path[oldSize] = (Pos*)malloc(sizeof(Pos));
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
