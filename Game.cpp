﻿#include "OceanInvaders.h"
#include "Game.h"

//Private functions

void Game::initVariables() 
{
	this->window = nullptr;
	gameState = GameState::Running;
	this->gameFont.loadFromFile("Assets/Fonts/PressStart2P.ttf");
	this->gameMessage.setFont(gameFont);
	this->gameMessage.setCharacterSize(64);
	this->gameMessage.setFillColor(sf::Color::White);
}

void Game::initWindow()
{
	this->videoMode.width = WINDOW_WIDTH;
	this->videoMode.height = WINDOW_HEIGHT;
	this->windowIcon.loadFromFile("Assets/Images/jellyFish2.png");
	this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), "Ocean Invaders", sf::Style::Titlebar | sf::Style::Close);
	this->window->setIcon(this->windowIcon.getSize().x, this->windowIcon.getSize().y, this->windowIcon.getPixelsPtr());
	this->backgroundTexture.loadFromFile("Assets/Images/ocean.jpg");
	this->windowBackground.setTexture(this->backgroundTexture);
	this->backgroundMusic.openFromFile("Assets/Audio/8BitRetroFunk.ogg");
	this->backgroundMusic.setLoop(true);
	this->backgroundMusic.play();
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
	//Player bullet touching allien
	std::vector<Bullet>* playerBulletsPtr = this->player.getBullets();
	for (int i = 0; i < playerBulletsPtr->size(); i++) {
		if (this->enemies.checkBulletColision(playerBulletsPtr->at(i).getBounds())) {
			playerBulletsPtr->erase(playerBulletsPtr->begin() + i);
		}
	}

	//Enemy bullet touching player
	std::vector<Bullet>* enemiesBulletsPtr = this->enemies.getBullets();
	for (int i = 0; i < enemiesBulletsPtr->size(); i++) {
		if (this->player.checkBulletColision(enemiesBulletsPtr->at(i).getBounds())) {
			this->gameState = GameState::GameOver;
		}
	}

	//Alien touching player
	if (this->enemies.checkPlayerColision(this->player.getBounds())) {
		this->gameState = GameState::GameOver;
	}
}

void Game::update() {
	this->pollEvents();
	if (this->gameState == GameState::Running) {
		this->updateColisions();
		this->player.update();
		this->enemies.update();
	}
	else if (this->gameState == GameState::Win) {
			this->gameMessage.setString(L"Wygrałeś");
			this->gameMessage.setPosition(sf::Vector2f(145.f, 250.f));
	}
	else if (this->gameState == GameState::GameOver) {
			this->gameMessage.setString(L"Koniec gry");
			this->gameMessage.setPosition(sf::Vector2f(125.f, 250.f));
	}

	if (this->enemies.getCount() == 0)
		gameState = GameState::Win;
}

void Game::render() {
	this->window->clear();
	this->window->draw(this->windowBackground);
	//Render game window
	if (this->gameState == GameState::Running) {
		this->player.render(this->window);
		this->enemies.render(this->window);
	}
	else {
		this->window->draw(this->gameMessage);
	}
	this->window->display();
}