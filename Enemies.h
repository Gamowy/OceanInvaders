#pragma once
#include "GalaxyInvaders.h"
#include "Alien.h"
#include "Bullet.h"
#include <vector>

class Enemies {
private:
	//Variables
	int enemyCount = ALIEN_ROW * ALIEN_COL;
	int moveType, nextMoveType, moveDownLimiter, moveDownCounter;
	int aliensLeftBoundry, aliensRightBoundry;
	Alien** aliens;
	std::vector<Bullet> bullets;
	sf::Clock shootDelay;
	int enemyMap[ALIEN_ROW][ALIEN_COL] ={ {1,1,1,1,1,1,1,1,1,1},
										  {2,2,2,2,2,2,2,2,2,2},
										  {3,3,3,3,3,3,3,3,3,3},
					                      {3,3,3,3,3,3,3,3,3,3},
					                      {2,2,2,2,2,2,2,2,2,2},
					                      {1,1,1,1,1,1,1,1,1,1} };
	void initEnemies();
	void move();
	void shoot();

public:
	//Constructor / Deconstructor
	Enemies();
	virtual ~Enemies();

	//Functions
	int getCount();
	std::vector<Bullet>* getBullets();
	bool checkBulletColision(sf::FloatRect bulletBounds);
	bool checkPlayerColision(sf::FloatRect playerBounds);
	void update();
	void render(sf::RenderTarget* target);
};