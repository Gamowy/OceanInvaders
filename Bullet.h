#pragma once
#include "OceanInvaders.h"

class Bullet 
{
private:
	//Variables
	unsigned short type;
	sf::Sprite bubble;

public:
	//Constructor / Destructor
	Bullet(sf::Vector2f objectPos, int source, sf::Texture* bubbleTexture);
	virtual ~Bullet();

	//Functions
	sf::FloatRect getBounds();
	void move();
	bool outOfWindow();
	void update();
	void render(sf::RenderTarget* target);
};