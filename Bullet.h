#pragma once
#include "GalaxyInvaders.h"

class Bullet {
private:
	//Variables
	int type;
	sf::RectangleShape rect;

public:
	//Constructor / Deconstructor
	Bullet(sf::Vector2f objectPos, int source);
	virtual ~Bullet();

	//Functions
	sf::FloatRect getBounds();
	void move();
	bool outOfWindow();
	void update();
	void render(sf::RenderTarget* target);
};