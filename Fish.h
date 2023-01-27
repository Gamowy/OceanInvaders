#pragma once
#include "OceanInvaders.h"
class Fish {
private:
	//Variables
	int type = 0;
	sf::Texture texture1, texture2;
	sf::Sprite sprite;
	sf::Clock spriteAnimationDelay;

public:
	//Constructor / Deconstructor
	Fish();
	virtual ~Fish();

	//Functions
	void initFish(int type);
	int getType();
	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
	void place(sf::Vector2f vector);
	void move(sf::Vector2f vector);
	void kill();
	bool checkWindowColision(sf::Vector2f vector);
	void render(sf::RenderTarget* target);
};