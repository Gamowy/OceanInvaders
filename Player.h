#include "GalaxyInvaders.h"
#include "Bullet.h"

#pragma once
class Player {
private:
	//Variables
	sf::Texture shipTexture;
	sf::Sprite ship;
	sf::Vector2f shipPosition;
	sf::Clock shootDelay;
	std::vector<Bullet> bullets;

public:
	//Constructor / Deconstructor
	Player();
	virtual ~Player();

	//Accessors
	sf::Sprite getShip();
	std::vector<Bullet>* getBullets();

	//Functions
	sf::FloatRect getBounds();
	bool checkBulletColision(sf::FloatRect bulletBounds);
	void moveShip();
	void shoot();
	
	void update();
	void render(sf::RenderTarget* target);
};