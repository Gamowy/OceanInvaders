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
	moveDownCounter++;
}
//Movement types DOWN = 0, LEFT = 1, RIGHT = 2
void Enemies::move() {
	sf::Vector2f moveSpeed;
	switch (moveType) {
	case 0:
		moveSpeed.x = 0.f;
		moveSpeed.y = ALIEN_SPEED;
		moveDownLimiter += ALIEN_SPEED;
		moveDownCounter++;
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

std::mt19937 mt(time(nullptr));
void Enemies::shoot() {
	if (this->shootDelay.getElapsedTime().asSeconds() > ALIEN_BULLET_DELAY) {
		int shooterIndex;
		std::vector <int> possibleShooters;
		for (int i = 0; i < ALIEN_ROW; i++) {
			for (int j = 0; j < ALIEN_COL; j++) {
				if (this->aliens[i][j].getType() != 0)
					possibleShooters.push_back(i * 10 + j);
			}
		}
		shooterIndex = possibleShooters.at(mt() % possibleShooters.size());
		this->bullets.push_back(Bullet(this->aliens[shooterIndex / 10][shooterIndex % 10].getPosition(), 1));
		shootDelay.restart();
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

int Enemies::getCount() {
	return this->enemyCount;
}

std::vector<Bullet>* Enemies::getBullets()
{
	return &this->bullets;
}

bool Enemies::checkBulletColision(sf::FloatRect bulletBounds)
{
	sf::FloatRect alienBounds;
	for (int i = 0; i < ALIEN_ROW; i++) {
		for (int j = 0; j < ALIEN_COL; j++) {
			if (this->aliens[i][j].getType() != 0) {
				alienBounds = this->aliens[i][j].getBounds();
				if (alienBounds.intersects(bulletBounds)) {
					this->aliens[i][j].kill();
					enemyCount--;
					return true;
				}
			}
		}
	}
	return false;
}

bool Enemies::checkPlayerColision(sf::FloatRect playerPosition) {
	sf::FloatRect alienBounds;
	if (this->moveDownCounter > 11) {
		for (int i = 0; i < ALIEN_ROW; i++) {
			for (int j = 0; j < ALIEN_COL; j++) {
				if (this->aliens[i][j].getType() != 0) {
					alienBounds = this->aliens[i][j].getBounds();
					if (alienBounds.intersects(playerPosition)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Enemies::update()
{
	this->move();
	this->shoot();

	//Update bullets
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i).update();
		if (this->bullets.at(i).outOfWindow())
		{
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Enemies::render(sf::RenderTarget* target)
{
	//Render Aliens
	for (int i = 0; i < ALIEN_ROW; i++) {
		for (int j = 0; j < ALIEN_COL; j++) {
			if (this->aliens[i][j].getType() != 0)
			this->aliens[i][j].render(target);
		}
	}
	//Render Alien bullets
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i).render(target);
	}
}