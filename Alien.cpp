#include "GalaxyInvaders.h"
#include "Alien.h"

//Constructor / Deconstructor
Alien::Alien() 
{

}

Alien::~Alien() 
{

}

void Alien::initAlien(int type) {
	switch (type) {
	case 1: 
		this->type = 1;
		this->texture.loadFromFile("Resources/Images/orangeAlien.png");
		this->sprite.setTexture(texture);
		break;
	case 2:
		this->type = 2;
		this->texture.loadFromFile("Resources/Images/greenAlien.png");
		this->sprite.setTexture(texture);
		break;
	case 3:
		this->type = 3;
		this->texture.loadFromFile("Resources/Images/blueAlien.png");
		this->sprite.setTexture(texture);
		break;
	}
}

int Alien::getType() {
	return this->type;
}

void Alien::place(sf::Vector2f vector) {
	this->sprite.setPosition(vector);
}

void Alien::move(sf::Vector2f vector) {
	this->sprite.move(vector);
}

bool Alien::checkWindowColision(sf::Vector2f vector) {
	if (this->sprite.getPosition().x + vector.x < 0.f || this->sprite.getPosition().x + vector.x > WINDOW_WIDTH - ALIEN_WIDTH)
		return true;
	else
		return false;
}

void Alien::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
}