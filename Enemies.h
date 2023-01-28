#pragma once
#include "OceanInvaders.h"
#include "Fish.h"
#include "Bullet.h"
#include <vector>

class Enemies 
{
private:
	//Variables
	unsigned short enemyCount = FISH_ROW * FISH_COL;
	unsigned short moveType{}, nextMoveType{}, moveDownLimiter{}, moveDownCounter{};
	Fish** fishes;
	std::vector<Bullet> bullets;
	sf::Texture bulletTexture;
	float bulletDelay;
	sf::Clock shootDelay;
	unsigned short enemyMap[FISH_ROW][FISH_COL];

	//Private Functions
	void initEnemies();
	void move();
	void shoot();

public:
	//Constructor / Destructor
	Enemies(float bulletDelayValue);
	virtual ~Enemies();

	//Functions
	int getCount();
	std::vector<Bullet>* getBullets();
	bool checkBulletColision(sf::FloatRect bulletBounds);
	bool checkPlayerColision(sf::FloatRect playerBounds);
	void update();
	void render(sf::RenderTarget* target);
};