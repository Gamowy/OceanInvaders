#include "GalaxyInvaders.h"
#include "Bullet.h"

//Constructor / Deconstructor
Bullet::Bullet(sf::Vector2f playerPos)
{
	this->rect.setSize(sf::Vector2f(10.f, 20.f));
	this->rect.setPosition(sf::Vector2f(playerPos.x + 25.f, playerPos.y));
}

Bullet::~Bullet()
{

}

//Functions

sf::Vector2f Bullet::getPos() {
	return this->rect.getPosition();
}


void Bullet::move() {
	this->rect.move(sf::Vector2f(0.f, -BULLET_SPEED));
}

bool Bullet::outOfWindow()
{
	if (this->rect.getPosition().y < -20.f)
		return true;
	else
		return false;
}

void Bullet::update()
{
	this->move();
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->rect);
}