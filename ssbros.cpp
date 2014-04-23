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
#include "SmartHero.hpp"
#include "SmartEnemy.hpp"
#include "SmartPowerup.hpp"
#include <stdlib.h>

int main( int argc, char** argv )
{
	Actor** actors = (Actor**) malloc(10 * sizeof(Actor*));
	
	actors[0] = new simplehero(ACTOR_HERO);
	actors[1] = new SmartHero(ACTOR_HERO);
	actors[2] = new SmartEnemy(ACTOR_ENEMY);
	actors[3] = new SmartPowerup(ACTOR_POWERUP);
	int num_actors = 4;

	GameManager* manager = new GameManager(argc, argv, actors, num_actors);
	manager->addActor(new Actor(ACTOR_HERO));
	manager->play();

	delete manager;
	manager = 0;

	for ( int i = 0; i < num_actors; i++ )
	{
		delete actors[i];
	}
	free(actors);
	actors = 0;
	return 0;
}
