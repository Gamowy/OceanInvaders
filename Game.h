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
	sf::Image windowIcon;
	sf::Texture backgroundTexture;
	sf::Sprite windowBackground;
	sf::Music backgroundMusic;
	sf::Font gameFont;
	sf::Text gameMessage;
	sf::Event ev;

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
	void pollEvents();
	void updateColisions();
	void update();
	void render();
};