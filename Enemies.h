#pragma once
#include "GalaxyInvaders.h"
#include "Alien.h"

class Enemies {
private:
	//Variables
	int enemyCount = ALIEN_ROW * ALIEN_COL;
	int moveType, nextMoveType, moveDownLimiter;
	int aliensLeftBoundry, aliensRightBoundry;
	Alien** aliens;
	int enemyMap[ALIEN_ROW][ALIEN_COL] ={ {1,1,1,1,1,1,1,1,1,1},
										  {1,1,1,1,1,1,1,1,1,1},
										  {2,2,2,3,3,3,3,2,2,2},
					                      {2,2,2,3,3,3,3,2,2,2},
					                      {1,1,1,1,1,1,1,1,1,1},
					                      {2,2,2,2,2,2,2,2,2,2} };
	void initEnemies();
	void moveEnemies();

public:
	//Constructor / Deconstructor
	Enemies();
	virtual ~Enemies();

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};