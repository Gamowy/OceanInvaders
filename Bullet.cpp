#include "OceanInvaders.h"
#include "Bullet.h"

//Constructor / Deconstructor
//bullet types 0 - player bullet, 1 - fish bullet
Bullet::Bullet(sf::Vector2f objectPos, int source, sf::Texture* bubbleTexture)
{
	//Set bullet texture
	this->bubble.setTexture(*bubbleTexture);
	this->bubble.setScale(sf::Vector2f(1.25f, 1.25f));

	if (source == 0) 
	{
		//Player bullet
		type = 0;
		this->bubble.setPosition(sf::Vector2f(objectPos.x + 32.5f, objectPos.y - 20.f));
	}
	else 
	{
		//Fish bullet
		type = 1;
		this->bubble.setPosition(sf::Vector2f(objectPos.x + 15.f, objectPos.y + 32.f));
	}
}

Bullet::~Bullet()
{

}

//Functions

//Return bullet bounds
sf::FloatRect Bullet::getBounds() 
{
	return this->bubble.getGlobalBounds();
}

//Move bullet in direction
void Bullet::move() 
{
	if(type == 0)
		this->bubble.move(sf::Vector2f(0.f, -PLAYER_BULLET_SPEED));
	else
		this->bubble.move(sf::Vector2f(0.f, FISH_BULLET_SPEED));
}

//Check if if bullet is out of window
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

//Render bullet on screen
void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->bubble);
}