#include "OceanInvaders.h"
#include "Bullet.h"

//Constructor / Deconstructor
//bullet types 0 = player bullet, 1 = fish bullet

Bullet::Bullet(sf::Vector2f objectPos, int source, sf::Texture* bubbleTexture)
{
	this->bubble.setTexture(*bubbleTexture);
	this->bubble.setScale(sf::Vector2f(1.25f, 1.25f));

	if (source == 0) {
		type = 0;
		this->bubble.setPosition(sf::Vector2f(objectPos.x + 32.5f, objectPos.y - 20.f));
	}
	else 
	{
		type = 1;
		this->bubble.setPosition(sf::Vector2f(objectPos.x + 15.f, objectPos.y + 32.f));
	}
}

Bullet::~Bullet()
{

}

//Functions
sf::FloatRect Bullet::getBounds() {
	return this->bubble.getGlobalBounds();
}

void Bullet::move() {
	if(type == 0)
		this->bubble.move(sf::Vector2f(0.f, -BULLET_SPEED));
	else
		this->bubble.move(sf::Vector2f(0.f, FISH_BULLET_SPEED));
}

bool Bullet::outOfWindow()
{
	if (this->bubble.getPosition().y < 50.f || this->bubble.getPosition().y > WINDOW_HEIGHT)
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
	target->draw(this->bubble);
}