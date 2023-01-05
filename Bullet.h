#pragma once
#include "GalaxyInvaders.h"

class Bullet {
private:
	//Variables
	sf::RectangleShape rect;

public:
	//Constructor / Deconstructor
	Bullet(sf::Vector2f playerPos);
	virtual ~Bullet();

	//Functions
	void update();
	void move();
	void render(sf::RenderTarget* target);
};