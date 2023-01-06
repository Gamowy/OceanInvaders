#include "GalaxyInvaders.h"
#include "Bullet.h"

//Constructor / Deconstructor
//bullet types 0 = player bullet, 1 = allien bullet
Bullet::Bullet(sf::Vector2f objectPos, int source)
{
	this->rect.setSize(sf::Vector2f(5.f, 20.f));
	if (source == 0) {
		type = 0;
		this->rect.setPosition(sf::Vector2f(objectPos.x + 27.5f, objectPos.y));
		this->rect.setFillColor(sf::Color::White);
	}
	else 
	{
		type = 1;
		this->rect.setPosition(sf::Vector2f(objectPos.x + 19.5f, objectPos.y + 32.f));
		this->rect.setFillColor(sf::Color::Red);
	}
}

Bullet::~Bullet()
{

}


//Functions

sf::FloatRect Bullet::getBounds() {
	return this->rect.getGlobalBounds();
}


void Bullet::move() {
	if(type == 0)
		this->rect.move(sf::Vector2f(0.f, -BULLET_SPEED));
	else
		this->rect.move(sf::Vector2f(0.f, ALIEN_BULLET_SPEED));
}

bool Bullet::outOfWindow()
{
	if (this->rect.getPosition().y < -20.f || this->rect.getPosition().y > 600.f)
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