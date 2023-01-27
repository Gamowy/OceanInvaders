#include "OceanInvaders.h"
#include "Bullet.h"

//Constructor / Deconstructor
//bullet types 0 = player bullet, 1 = allien bullet
Bullet::Bullet(sf::Vector2f objectPos, int source)
{
	this->rect.setSize(sf::Vector2f(6.25f, 25.f));

	if (source == 0) {
		type = 0;
		this->rect.setPosition(sf::Vector2f(objectPos.x + 40.5f, objectPos.y - 20.f));
		this->rect.setFillColor(sf::Color::White);
	}
	else 
	{
		type = 1;
		this->rect.setPosition(sf::Vector2f(objectPos.x + 19.5f, objectPos.y + 32.f));
		this->rect.setFillColor(sf::Color::Green);
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
		this->rect.move(sf::Vector2f(0.f, FISH_BULLET_SPEED));
}

bool Bullet::outOfWindow()
{
	if (this->rect.getPosition().y < -20.f || this->rect.getPosition().y > WINDOW_HEIGHT)
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