#pragma once
#include "GalaxyInvaders.h"
#include "Player.h"
#include "Enemies.h"

/*
	Class that acts as the game core.
*/
class Game {
private:
	//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Texture backgroundTexture;
	sf::Sprite windowBackground;
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
	void update();
	void render();
};