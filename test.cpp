#include <stdio.h>
#include "Pos.hpp"


int main(int argc, char** argv)
{
	Pos* a = new Pos(1, 1);
	Pos* b = new Pos(2, 2);
	Pos* c = new Pos(1, 1);

	if(a->equals(c))
	{
		printf("a == c\n");
	}
	else
	{
		printf("a != c\n");
	}

}
