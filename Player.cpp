#include "OceanInvaders.h"
#include "Player.h"

//Constructor / Deconstructor
Player::Player(float bulletDelayValue)
{
	this->bulletDelay = bulletDelayValue;
	this->sharkTexture1.loadFromFile("Assets/Images/player1.png");
	this->sharkTexture2.loadFromFile("Assets/Images/player2.png");
	this->shark.setTexture(sharkTexture1);
	this->bulletTexture.loadFromFile("Assets/Images/bubble.png");
	this->shark.setPosition(sf::Vector2f(352.f, 805.f));
}

Player::~Player() 
{

}

//Accesors
sf::Sprite Player::getShark() 
{
	return this->shark;
}

//Return bullets fired by player
std::vector<Bullet>* Player::getBullets()
{
	return &this->bullets;
}

//Functions
sf::FloatRect Player::getBounds()
{
	return this->shark.getGlobalBounds();
}

//Check if a bullet hits player
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
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && this->shark.getPosition().x - PLAYER_SPEED >= 0.f) {

		this->shark.setTexture(this->sharkTexture2, true);
		this->shark.move(sf::Vector2f(-PLAYER_SPEED, 0.f));
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && this->shark.getPosition().x + PLAYER_SPEED <= WINDOW_WIDTH - 81.f) {
		this->shark.setTexture(this->sharkTexture1, true);
		this->shark.move(sf::Vector2f(PLAYER_SPEED, 0.f));
	}
}

//Create a bullet at player position
void Player::shoot() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootDelay.getElapsedTime().asSeconds() > this->bulletDelay) {
		this->bullets.push_back(Bullet(this->shark.getPosition(), 0, &bulletTexture));
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