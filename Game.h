#pragma once
#include "OceanInvaders.h"
#include "Player.h"
#include "Enemies.h"

//Possible game states
enum GameState {Menu, Running, Win, GameOver, End, Error};

class Game 
{
private:
	//Variables
	GameState gameState;
	unsigned int points;
	unsigned short levelsPlayed;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Image windowIcon;
	sf::Texture backgroundTexture;
	sf::Sprite windowBackground;
	sf::RectangleShape windowTint;
	sf::Music backgroundMusic;
	bool buttonWasReleased;
	//Time between player/fish firing bullets
	float fishBulletDelay;
	float playerBulletDelay;
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
	//Constructor / Destructor
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