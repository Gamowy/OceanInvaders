#include "GalaxyInvaders.h"
#include "Player.h"

//Constructor / Deconstructor
Player::Player()
{
	this->sharkPosition.x = 352.f;
	this->sharkPosition.y = 755.f;
	this->sharkTexture1.loadFromFile("Assets/Images/player1.png");
	this->sharkTexture2.loadFromFile("Assets/Images/player2.png");
	this->shark.setTexture(sharkTexture1);
	this->shark.setPosition(sharkPosition);
}

Player::~Player() 
{

}

//Accesors
sf::Sprite Player::getShark() 
{
	return this->shark;
}

std::vector<Bullet>* Player::getBullets()
{
	return &this->bullets;
}

//Functions
sf::FloatRect Player::getBounds()
{
	return this->shark.getGlobalBounds();
}

bool Player::checkBulletColision(sf::FloatRect bulletBounds)
{
	sf::FloatRect playerBounds = this->shark.getGlobalBounds();
	if (bulletBounds.intersects(playerBounds))
		return true;
	else
		return false;
}

void Player::moveShark() 
{
	//Player movement
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && this->sharkPosition.x - PLAYER_SPEED >= 0.f) {
		this->sharkPosition.x -= PLAYER_SPEED;
		this->shark.setTexture(this->sharkTexture2, true);
		this->shark.setPosition(sharkPosition);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && this->sharkPosition.x + PLAYER_SPEED <= WINDOW_WIDTH - 81.f) {
		this->sharkPosition.x += PLAYER_SPEED;
		this->shark.setTexture(this->sharkTexture1, true);
		this->shark.setPosition(sharkPosition);
	}
}

void Player::shoot() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootDelay.getElapsedTime().asSeconds() > BULLET_DELAY) {
		this->bullets.push_back(Bullet(this->sharkPosition, 0));
		this->shootDelay.restart();
	}
}

void Player::update() 
{
	this->moveShark();
	this->shoot();
	//Update bullets
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i).update();
		if (this->bullets.at(i).outOfWindow()) 
		{
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Player::render(sf::RenderTarget* target) 
{
	target->draw(this->shark);
	//Render bullets shot
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets.at(i).render(target);
	}
}