#pragma once
#include "OceanInvaders.h"

class Bullet {
private:
	//Variables
	int type;
	sf::Sprite bubble;

public:
	//Constructor / Deconstructor
	Bullet(sf::Vector2f objectPos, int source, sf::Texture* bubbleTexture);
	virtual ~Bullet();

	//Functions
	sf::FloatRect getBounds();
	void move();
	bool outOfWindow();
	void update();
	void render(sf::RenderTarget* target);
};