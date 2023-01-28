#include "OceanInvaders.h"
#include "Game.h"

//Private functions

void Game::initVariables() 
{
	buttonWasReleased = true;
	this->window = nullptr;
	this->gameState = GameState::Menu;
	this->player = nullptr;
	this->enemies = nullptr;

	//Text
	this->gameFont1.loadFromFile("Assets/Fonts/PressStart2P.ttf");
	this->gameFont2.loadFromFile("Assets/Fonts/VT323.ttf");
	this->gameMessage.setOutlineThickness(1.f);
	this->gameMessage.setOutlineColor(sf::Color::Black);
	this->gameMessage.setFillColor(sf::Color::White);
	this->spacebarTexture.loadFromFile("Assets/Images/spacebar.png");
	this->spacebarImg.setTexture(spacebarTexture);

	//Window Background
	this->backgroundTexture.loadFromFile("Assets/Images/ocean.jpg");
	this->windowBackground.setTexture(this->backgroundTexture);

	//Music
	this->backgroundMusic.openFromFile("Assets/Audio/8BitRetroFunk.ogg");
	this->backgroundMusic.setLoop(true);
	this->backgroundMusic.play();
}

void Game::initObjects() {
	this->player = new Player;
	this->enemies = new Enemies;
}

void Game::destroyObjects() {
	delete this->player, enemies;
}

void Game::initWindow()
{
	this->videoMode.width = WINDOW_WIDTH;
	this->videoMode.height = WINDOW_HEIGHT;
	this->windowIcon.loadFromFile("Assets/Images/jellyFish2.png");
	this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), "Ocean Invaders", sf::Style::Titlebar | sf::Style::Close);
	this->window->setIcon(this->windowIcon.getSize().x, this->windowIcon.getSize().y, this->windowIcon.getPixelsPtr());
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
			if (this->ev.key.code == sf::Keyboard::Space && buttonWasReleased && (this->gameState == GameState::Menu || this->gameState == GameState::Win)) {
				this->initObjects();
				this->gameState = GameState::Running;
			}
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			buttonWasReleased = false;
			break;
		case sf::Event::KeyReleased:
			buttonWasReleased = true;
			break;
		}
	}
}

void Game::updateColisions()
{	
	//Player bullet touching allien
	std::vector<Bullet>* playerBulletsPtr = this->player->getBullets();
	for (int i = 0; i < playerBulletsPtr->size(); i++) {
		if (this->enemies->checkBulletColision(playerBulletsPtr->at(i).getBounds())) {
			playerBulletsPtr->erase(playerBulletsPtr->begin() + i);
		}
	}

	//Enemy bullet touching player
	std::vector<Bullet>* enemiesBulletsPtr = this->enemies->getBullets();
	for (int i = 0; i < enemiesBulletsPtr->size(); i++) {
		if (this->player->checkBulletColision(enemiesBulletsPtr->at(i).getBounds())) {
			this->gameState = GameState::GameOver;
			return;
		}
	}

	//Alien touching player
	if (this->enemies->checkPlayerColision(this->player->getBounds())) {
		this->gameState = GameState::GameOver;
		return;
	}
}

void Game::update() {
	this->pollEvents();

	switch (this->gameState) {
	case GameState::Running:
		this->updateColisions();
		this->player->update();
		this->enemies->update();
		if (this->enemies->getCount() == 0)
			gameState = GameState::Win;
		break;

	case GameState::Win:
		this->gameMessage.setFont(gameFont1);
		this->gameMessage.setString(L"Wygrałeś");
		this->gameMessage.setPosition(sf::Vector2f(145.f, 250.f));
		break;

	case GameState::GameOver:
		this->gameMessage.setFont(gameFont1);
		this->gameMessage.setString(L"Koniec gry");
		this->gameMessage.setPosition(sf::Vector2f(125.f, 250.f));
		break;
	}
}

void Game::renderMenu() {
	this->gameMessage.setFont(gameFont1);
	this->gameMessage.setStyle(sf::Text::Regular);
	this->gameMessage.setCharacterSize(48);

	// "Ocean Invaders"
	this->gameMessage.setString(L"Ocean Invaders");
	this->gameMessage.setPosition(sf::Vector2f(66.f, 10.f));
	this->window->draw(gameMessage);

	//Opis
	this->gameMessage.setCharacterSize(42);
	this->gameMessage.setFont(gameFont2);
	this->gameMessage.setOutlineThickness(0.7f);

	this->gameMessage.setString(L"Celem gry jest pokonanie morskich stworzeń i");
	this->gameMessage.setPosition(sf::Vector2f(10.f, 100.f));
	this->window->draw(gameMessage);

	this->gameMessage.setString(L"dostanie się na dno oceanu. Twoi przeciwnicy ");
	this->gameMessage.setPosition(sf::Vector2f(10.f, 140.f));
	this->window->draw(gameMessage);

	this->gameMessage.setString(L"stają się coraz bardziej agresywni, im głębiej");
	this->gameMessage.setPosition(sf::Vector2f(10.f, 180.f));
	this->window->draw(gameMessage);

	this->gameMessage.setString(L"schodzisz. Czy uda ci się dostać na same dno");
	this->gameMessage.setPosition(sf::Vector2f(10.f, 220.f));
	this->window->draw(gameMessage);

	this->gameMessage.setString(L"Rowu Mariańskiego? (11 034 m p.p.m.)");
	this->gameMessage.setPosition(sf::Vector2f(10.f, 260.f));
	this->window->draw(gameMessage);

	//Sterowanie
	this->gameMessage.setStyle(sf::Text::Underlined);
	this->gameMessage.setString(L"Sterowanie");
	this->gameMessage.setPosition(sf::Vector2f(314.f, 320.f));
	this->window->draw(gameMessage);

	this->gameMessage.setStyle(sf::Text::Regular);
	this->gameMessage.setString(L"Ruch graczem:");
	this->gameMessage.setPosition(sf::Vector2f(10.f, 380.f));
	this->window->draw(gameMessage);


	sf::Texture aKeyTexture;
	aKeyTexture.loadFromFile("Assets/Images/aButton.png");
	sf::Sprite aKey(aKeyTexture);
	aKey.setPosition(230.f, 385.f);
	this->window->draw(aKey);

	sf::Texture dKeyTexture;
	dKeyTexture.loadFromFile("Assets/Images/dButton.png");
	sf::Sprite dKey(dKeyTexture);
	dKey.setPosition(275.f, 385.f);
	this->window->draw(dKey);

	sf::Texture leftArrTexture;
	leftArrTexture.loadFromFile("Assets/Images/leftArr.png");
	sf::Sprite leftArrKey(leftArrTexture);
	leftArrKey.setPosition(330.f, 385.f);
	this->window->draw(leftArrKey);

	sf::Texture rightArrTexture;
	rightArrTexture.loadFromFile("Assets/Images/rightArr.png");
	sf::Sprite rightArrKey(rightArrTexture);
	rightArrKey.setPosition(375.f, 385.f);
	this->window->draw(rightArrKey);

	this->gameMessage.setString(L"Strzelanie:");
	this->gameMessage.setPosition(sf::Vector2f(10.f, 450.f));
	this->window->draw(gameMessage);

	this->spacebarImg.setPosition(sf::Vector2f(200.f, 455.f));
	this->window->draw(spacebarImg);

	//Rozpocznij
	this->gameMessage.setString(L"Powodzenia!");
	this->gameMessage.setPosition(sf::Vector2f(309.f, 525.f));
	this->window->draw(gameMessage);

	this->spacebarImg.setPosition(sf::Vector2f(290.f, 730.f));
	this->gameMessage.setString(L"Naciśnij         aby rozpocząć");
	this->gameMessage.setPosition(sf::Vector2f(145.f, 725.f));
	this->window->draw(gameMessage);
	this->window->draw(spacebarImg);

}

void Game::render() {
	this->window->clear();
	this->window->draw(this->windowBackground);

	//Render game window
	switch (this->gameState) {
		case GameState::Menu:;
			this->renderMenu();
			break;

		case GameState::Running:
			this->player->render(this->window);
			this->enemies->render(this->window);
			break;

		default:
			this->window->draw(this->gameMessage);
			break;
	}

	this->window->display();
}