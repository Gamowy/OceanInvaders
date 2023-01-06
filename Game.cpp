#include "GalaxyInvaders.h"
#include "Game.h"

//Private functions
void Game::initVariables() 
{
	this->window = nullptr;
	gameOver = 0;
}

void Game::initWindow()
{
	this->videoMode.width = WINDOW_WIDTH;
	this->videoMode.height = WINDOW_HEIGHT;
	this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), "GalaxyInvaders", sf::Style::Titlebar | sf::Style::Close);
	this->backgroundTexture.loadFromFile("Resources/Images/space.png");
	this->windowBackground.setTexture(this->backgroundTexture);
	this->window->setFramerateLimit(FRAME_RATE);
}

//Constructor / Deconstructor
Game::Game() 
{
	this->initVariables();
	this->initWindow();
}

Game::~Game() 
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions
void Game::pollEvents() 
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) 
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}

void Game::updateColisions()
{	
	//Bullet touching allien
	std::vector<Bullet>* bulletsPtr = this->player.getBullets();
	for (int i = 0; i < bulletsPtr->size(); i++) {
		if (this->enemies.checkBulletColision(bulletsPtr->at(i).getBounds())) {
			bulletsPtr->erase(bulletsPtr->begin() + i);
		}
	}

	//Alien touching player
	if (this->enemies.checkPlayerColision(this->player.getBounds())) {
		gameOver = -1;
	}
}

void Game::update() {
	if (!gameOver) {
		this->pollEvents();
		this->updateColisions();
		this->player.update();
		this->enemies.update();
	}
	else {
		if (gameOver > 0)
			std::cout << "You won.";
		else
			std::cout << "Game over.";
		this->window->close();
	}
}

void Game::render() {
	this->window->clear();

	//Render game window
	this->window->draw(this->windowBackground);
	this->player.render(this->window);
	this->enemies.render(this->window);

	this->window->display();
}