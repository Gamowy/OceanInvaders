#include "GalaxyInvaders.h"
#include "Enemies.h"

//Private Functions
void Enemies::initEnemies()
{
	for (int i = 0; i < ALIEN_ROW; i++) {
		for (int j = 0; j < ALIEN_COL; j++) {
			aliens[i][j].initAlien(enemyMap[i][j]);
			this->aliens[i][j].place(sf::Vector2f(50.f * j, 38.f * i));
		}
	}
	moveType = 2;
	nextMoveType = 0;
	moveDownLimiter = 0;
}
//Movement types DOWN = 0, LEFT = 1, RIGHT = 2
void Enemies::moveEnemies() {
	sf::Vector2f moveSpeed;
	switch (moveType) {
	case 0:
		moveSpeed.x = 0.f;
		moveSpeed.y = ALIEN_SPEED;
		moveDownLimiter += ALIEN_SPEED;
		break;
	case 1:
		moveSpeed.x = -ALIEN_SPEED;
		moveSpeed.y = 0.f;
		break;
	case 2:
		moveSpeed.x = ALIEN_SPEED;
		moveSpeed.y = 0.f;
		break;
	}

	for (int i = 0; i < ALIEN_ROW; i++) {
		for (int j = 0; j < ALIEN_COL; j++) {
			if (this->aliens[i][j].getType() != 0) {
				this->aliens[i][j].move(moveSpeed);
				if (moveType != 0 && this->aliens[i][j].checkWindowColision(moveSpeed)) {
					nextMoveType = (moveType == 1) ? 2 : 1;
					moveType = 0;
					moveDownLimiter = 0;
					break;
				}
			}
		}
	}
	if (moveDownLimiter > ALIEN_HEIGHT) {
		moveType = nextMoveType;
	}
}

//Constructor / Deconstructor
Enemies::Enemies() 
{
	aliens = new Alien*[ALIEN_ROW];
	for (int i = 0; i < ALIEN_ROW; i++) {
		aliens[i] = new Alien[ALIEN_COL];
	}
	this->initEnemies();
}

Enemies::~Enemies() 
{
	for (int i = 0; i < ALIEN_ROW; i++) {
		delete[] aliens[i];
	}
	delete[] aliens;
}

//Functions

void Enemies::update()
{
	this->moveEnemies();
}

void Enemies::render(sf::RenderTarget* target)
{
	for (int i = 0; i < ALIEN_ROW; i++) {
		for (int j = 0; j < ALIEN_COL; j++) {
			if (this->aliens[i][j].getType() != 0)
			this->aliens[i][j].render(target);
		}
	}
}