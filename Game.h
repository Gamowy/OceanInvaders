#pragma once
#include "OceanInvaders.h"
#include "Player.h"
#include "Enemies.h"

enum GameState {Menu, Running, Win, GameOver, End, Error};

class Game {
private:
	//Variablesz
	unsigned int points, levelsPlayed;
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
	sf::Text depthText, pointsText;

	//Game objects
	Player* player;
	Enemies* enemies;

	//Private functions
	void initVariables();
	void initGame();
	void updateVariables();
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