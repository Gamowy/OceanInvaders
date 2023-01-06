#include "GalaxyInvaders.h"
#include "Alien.h"
#include "Bullet.h"

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

sf::Vector2f Alien::getPosition() {
	return this->sprite.getPosition();
}

sf::FloatRect Alien::getBounds() {
	return this->sprite.getGlobalBounds();
}

void Alien::place(sf::Vector2f vector) {
	this->sprite.setPosition(vector);
}

void Alien::move(sf::Vector2f vector) {
	this->sprite.move(vector);
}

void Alien::kill() {
	this->type = 0;
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