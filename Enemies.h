#pragma once
#include "OceanInvaders.h"
#include "Fish.h"
#include "Bullet.h"
#include <vector>

class Enemies {
private:
	//Variables
	int enemyCount = FISH_ROW * FISH_COL;
	int moveType, nextMoveType, moveDownLimiter, moveDownCounter;
	int aliensLeftBoundry, aliensRightBoundry;
	Fish** fishes;
	std::vector<Bullet> bullets;
	sf::Clock shootDelay;
	int enemyMap[FISH_ROW][FISH_COL];

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