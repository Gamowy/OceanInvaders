#include "GalaxyInvaders.h"
#include "Player.h"

//Constructor / Deconstructor
Player::Player()
{
	this->shipPosition.x = 270.f;
	this->shipPosition.y = 570.f;
	this->shipTexture.loadFromFile("Resources/Images/player.png");
	this->ship.setTexture(shipTexture);
	this->ship.setPosition(shipPosition);
}

Player::~Player() 
{

}

//Accesors
sf::Sprite Player::getShip() 
{
	return this->ship;
}

//Functions
void Player::moveShip() 
{
	//Player movement
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && this->shipPosition.x - PLAYER_SPEED >= 0.f) {
		this->shipPosition.x -= PLAYER_SPEED;
		this->ship.setPosition(shipPosition);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && this->shipPosition.x + PLAYER_SPEED <= WINDOW_WIDTH - 60.f) {
		this->shipPosition.x += PLAYER_SPEED;
		this->ship.setPosition(shipPosition);
	}
}

void Player::shoot() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootDelay.getElapsedTime().asSeconds() > SHOOTING_SPEED) {
		this->bullets.push_back(Bullet(this->shipPosition));
		this->shootDelay.restart();
	}
}

void Player::update() 
{
	this->moveShip();
	this->shoot();
	//Update bullets
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i).update();
	}
}

void Player::render(sf::RenderTarget* target) 
{
	target->draw(this->ship);
	//Render bullets shot
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i).render(target);
	}
}