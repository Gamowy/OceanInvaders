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
	sf::Vector2f getPos();
	void move();
	bool outOfWindow();
	void update();
	void render(sf::RenderTarget* target);
};