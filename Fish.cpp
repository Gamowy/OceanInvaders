#include "OceanInvaders.h"
#include "Fish.h"
#include "Bullet.h"

//Constructor / Deconstructor
Fish::Fish() 
{

}

Fish::~Fish() 
{

}

//Create fish depending on type (Red Fish - 1, Purple Fish - 2, Jelly Fish - 3)
void Fish::initFish(int type) {
	switch (type) {
	case 1: 
		this->type = 1;
		this->texture1.loadFromFile("Assets/Images/redFish1.png");
		this->texture2.loadFromFile("Assets/Images/redFish2.png");
		this->sprite.setTexture(texture1);
		this->sprite.scale(3.5f, 3.5f);
		break;
	case 2:
		this->type = 2;
		
		this->texture1.loadFromFile("Assets/Images/purpleFish1.png");
		this->texture2.loadFromFile("Assets/Images/purpleFish2.png");
		this->sprite.setTexture(texture1);
		this->sprite.scale(3.5f, 3.5f);
		break;
	case 3:
		this->type = 3;
		this->texture1.loadFromFile("Assets/Images/jellyFish1.png");
		this->texture2.loadFromFile("Assets/Images/jellyFish2.png");
		this->sprite.setTexture(texture1);
		this->sprite.scale(3.5f, 3.5f);
		break;
	}
}

//Return type of fish
int Fish::getType() {
	return this->type;
}

//Return position of fish
sf::Vector2f Fish::getPosition() {
	return this->sprite.getPosition();
}

//Return bounds of fish
sf::FloatRect Fish::getBounds() {
	return this->sprite.getGlobalBounds();
}

//Set position of fish
void Fish::place(sf::Vector2f vector) {
	this->sprite.setPosition(vector);
}

//Move fish by vector
void Fish::move(sf::Vector2f vector) {
	if (this->spriteAnimationDelay.getElapsedTime().asSeconds() > 2 * FISH_ANIMATION_TIME) {
			this->sprite.setTexture(texture1, true);
			spriteAnimationDelay.restart();
	}
	else if (this->spriteAnimationDelay.getElapsedTime().asSeconds() > FISH_ANIMATION_TIME) {
		this->sprite.setTexture(texture2, true);
	}
	this->sprite.move(vector);
}

//Kill fish if hit
void Fish::kill() {
	this->type = 0;
}

//Check if fish colides with border of window
bool Fish::checkWindowColision(sf::Vector2f vector) {
	if (this->sprite.getPosition().x + vector.x < 0.f || this->sprite.getPosition().x + vector.x > WINDOW_WIDTH - FISH_WIDTH)
		return true;
	else
		return false;
}

//Render fish
void Fish::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
}