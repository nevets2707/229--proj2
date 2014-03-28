/*
 * ssbros.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: stolee
 */

#include "GraphMap.hpp"
#include "GameManager.hpp"
#include "Actor.hpp"
#include "OtherActors.hpp"
#include "simplehero.hpp"
#include <stdlib.h>

int main( int argc, char** argv )
{
	
	Actor** actors = (Actor**) malloc(10 * sizeof(Actor*));
	int num_actors = 1;

	actors[0] = new simplehero(ACTOR_HERO);

	GameManager* manager = new GameManager(argc, argv, actors, num_actors);
	manager->addActor(new Actor(ACTOR_HERO));
	manager->play();

	delete manager;

	for ( int i = 0; i < num_actors; i++ )
	{
		delete actors[i];
	}
	free(actors);

	return 0;
}
