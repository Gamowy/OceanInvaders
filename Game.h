#pragma once
#include "OceanInvaders.h"
#include "Player.h"
#include "Enemies.h"
enum GameState {Menu, Running, Win, GameOver, Error};

class Game {
private:
	//Variables
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
	sf::Sprite spacebarImg;
	sf::Texture spacebarTexture;

	//Game objects
	Player player;
	Enemies enemies;

	//Private functions
	void initVariables();
	void initWindow();
public:
	//Constructor / Deconstructor
	Game();
	virtual ~Game();
	
	//Accessors
	const bool running() const;

	//Functions
	void renderMenu();
	void pollEvents();
	void updateColisions();
	void update();
	void render();
};