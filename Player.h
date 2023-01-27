#include "OceanInvaders.h"
#include "Bullet.h"

#pragma once
class Player {
private:
	//Variables
	sf::Texture sharkTexture1, sharkTexture2;
	sf::Sprite shark;
	sf::Vector2f sharkPosition;
	sf::Clock shootDelay;
	std::vector<Bullet> bullets;

public:
	//Constructor / Deconstructor
	Player();
	virtual ~Player();

	//Accessors
	sf::Sprite getShark();
	std::vector<Bullet>* getBullets();

	//Functions
	sf::FloatRect getBounds();
	bool checkBulletColision(sf::FloatRect bulletBounds);
	void moveShark();
	void shoot();
	
	void update();
	void render(sf::RenderTarget* target);
};