#pragma once
#include "OceanInvaders.h"
#include "Player.h"
#include "Enemies.h"
enum GameState {Menu, Running, Win, GameOver, Error};

class Game {
private:
	//Variables
	bool buttonWasReleased;
	GameState gameState;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Image windowIcon;
	sf::Texture backgroundTexture;
	sf::Sprite windowBackground;
	sf::Music backgroundMusic;

	//Text Variables
	sf::Font gameFont1, gameFont2;
	sf::Text gameMessage;

	//Game objects
	Player* player;
	Enemies* enemies;

	//Private functions
	void initVariables();
	void initObjects();
	void destroyObjects();
	void initWindow();

public:
	//Constructor / Deconstructor
	Game();
	virtual ~Game();
	
	//Accessors
	const bool running() const;

	//Functions
	void renderMessage();
	void pollEvents();
	void updateColisions();
	void update();
	void render();
};