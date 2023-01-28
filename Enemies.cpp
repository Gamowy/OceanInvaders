#include "OceanInvaders.h"
#include "Enemies.h"
std::mt19937 mt(time(nullptr));

//Private Functions
void Enemies::initEnemies()
{
	for (int i = 0; i < FISH_ROW; i++) {
		for (int j = 0; j < FISH_COL; j++) {
			enemyMap[i][j] = mt() % 3 + 1;
			fishes[i][j].initFish(enemyMap[i][j]);
			this->fishes[i][j].place(sf::Vector2f(56.f * j, 56.f * i + 50.f));
		}
	}
	this->moveType = 2;
	this->bulletTexture.loadFromFile("Assets/Images/enemyBubble.png");
}

//Movement types (DOWN = 0, LEFT = 1, RIGHT = 2)
void Enemies::move() {
	sf::Vector2f moveSpeed;
	//Add speed in current direction of movement
	switch (moveType) {
	case 0:
		moveSpeed.x = 0.f;
		moveSpeed.y = FISH_SPEED;
		moveDownLimiter += FISH_SPEED;
		break;
	case 1:
		moveSpeed.x = -FISH_SPEED;
		moveSpeed.y = 0.f;
		break;
	case 2:
		moveSpeed.x = FISH_SPEED;
		moveSpeed.y = 0.f;
		break;
	}

	for (int i = 0; i < FISH_ROW; i++) {
		for (int j = 0; j < FISH_COL; j++) {
			if (this->fishes[i][j].getType() != 0) {
				//Move fish if still alive
				this->fishes[i][j].move(moveSpeed);
				//Change move type if fish hits window border
				if (moveType != 0 && this->fishes[i][j].checkWindowColision(moveSpeed)) {
					nextMoveType = (moveType == 1) ? 2 : 1;
					moveType = 0;
					break;
				}
			}
		}
	}
	//Limit how long fishes move down
	if (moveDownLimiter > FISH_HEIGHT) {
		moveType = nextMoveType;
		moveDownCounter++;
		moveDownLimiter = 0;
	}
}

//Randomly pick a fish to shoot and create a bullet at it's location
void Enemies::shoot() {
	if (this->shootDelay.getElapsedTime().asSeconds() > this->bulletDelay) {
		int shooterIndex;
		std::vector <int> possibleShooters;
		for (int i = 0; i < FISH_ROW; i++) {
			for (int j = 0; j < FISH_COL; j++) {
				if (this->fishes[i][j].getType() != 0)
					possibleShooters.push_back(i * 10 + j);
			}
		}
		shooterIndex = possibleShooters.at(mt() % possibleShooters.size());
		this->bullets.push_back(Bullet(this->fishes[shooterIndex / 10][shooterIndex % 10].getPosition(), 1, &bulletTexture));
		shootDelay.restart();
	}
}

//Constructor / Destructor
Enemies::Enemies(float bulletDelayValue) 
{
	this->bulletDelay = bulletDelayValue;
	fishes = new Fish*[FISH_ROW];
	for (int i = 0; i < FISH_ROW; i++) {
		fishes[i] = new Fish[FISH_COL];
	}
	this->initEnemies();
}

Enemies::~Enemies() 
{
	for (int i = 0; i < FISH_ROW; i++) {
		delete[] fishes[i];
	}
	delete[] fishes;
}

//Functions

//Return the amount of enemies alive
int Enemies::getCount() {
	return this->enemyCount;
}

//Return bullets shot by enemies
std::vector<Bullet>* Enemies::getBullets()
{
	return &this->bullets;
}

//Check if enemy is hit by a bullet
bool Enemies::checkBulletColision(sf::FloatRect bulletBounds)
{
	sf::FloatRect FishBounds;
	for (int i = 0; i < FISH_ROW; i++) {
		for (int j = 0; j < FISH_COL; j++) {
			if (this->fishes[i][j].getType() != 0) {
				FishBounds = this->fishes[i][j].getBounds();
				if (FishBounds.intersects(bulletBounds)) {
					this->fishes[i][j].kill();
					enemyCount--;
					return true;
				}
			}
		}
	}
	return false;
}

//Check if enemy colides with player
bool Enemies::checkPlayerColision(sf::FloatRect playerPosition) {
	sf::FloatRect FishBounds;
	if (this->moveDownCounter > 6) {
		for (int i = 0; i < FISH_ROW; i++) {
			for (int j = 0; j < FISH_COL; j++) {
				if (this->fishes[i][j].getType() != 0) {
					FishBounds = this->fishes[i][j].getBounds();
					if (FishBounds.intersects(playerPosition)) {
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
	//Render enemies
	for (int i = 0; i < FISH_ROW; i++) {
		for (int j = 0; j < FISH_COL; j++) {
			if (this->fishes[i][j].getType() != 0)
			this->fishes[i][j].render(target);
		}
	}
	//Render bullets
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i).render(target);
	}
}