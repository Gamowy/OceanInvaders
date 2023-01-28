#pragma once
#include "OceanInvaders.h"
#include "Bullet.h"

class Player 
{
private:
	//Variables
	sf::Texture sharkTexture1, sharkTexture2;
	sf::Texture bulletTexture;
	sf::Sprite shark;
	float bulletDelay;
	sf::Clock shootDelay;
	std::vector<Bullet> bullets;

public:
	//Constructor / Destructor
	Player(float bulletDelayValue);
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