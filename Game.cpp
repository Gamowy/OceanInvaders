#include "OceanInvaders.h"
#include "Game.h"

//Private functions

void Game::initVariables() 
{
	fishBulletDelay = 2.8f; //2.8f - 1.f
	playerBulletDelay = 0.3f; //0.3f - 1.f
	this->points = 0;
	this->levelsPlayed = 0;
	this->buttonWasReleased = true;
	this->window = nullptr;
	this->gameState = GameState::Menu;
	this->player = nullptr;
	this->enemies = nullptr;

	//Text
	this->gameFont1.loadFromFile("Assets/Fonts/PressStart2P.ttf");
	this->gameFont2.loadFromFile("Assets/Fonts/VT323.ttf");
	this->gameMessage.setOutlineThickness(1.f);
	this->gameMessage.setOutlineColor(sf::Color::Black);

	this->depthText.setCharacterSize(36);
	this->pointsText.setCharacterSize(36);
	this->depthText.setFont(gameFont2);
	this->depthText.setPosition(sf::Vector2f(400.f, 0.f));
	this->pointsText.setFont(gameFont2);
	this->pointsText.setPosition(sf::Vector2f(5.f, 0.f));
	this->depthText.setOutlineThickness(1.f);
	this->pointsText.setOutlineThickness(1.f);
	this->depthText.setOutlineColor(sf::Color::Black);
	this->pointsText.setOutlineColor(sf::Color::Black);


	//Window Background
	this->backgroundTexture.loadFromFile("Assets/Images/ocean.jpg");
	this->windowBackground.setTexture(this->backgroundTexture);
	this->windowTint.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	this->windowTint.setFillColor(sf::Color(0, 0, 0, 0));

	//Music
	this->backgroundMusic.openFromFile("Assets/Audio/8BitRetroFunk.ogg");
	this->backgroundMusic.setLoop(true);
	this->backgroundMusic.play();
}

void Game::initGame() {
	if (this->player != nullptr) {
		delete this->player, enemies;
	}
	this->player = new Player(playerBulletDelay);
	this->enemies = new Enemies(fishBulletDelay);
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
			if (this->ev.key.code == sf::Keyboard::Space && buttonWasReleased) {
				if ((this->gameState == GameState::Menu || this->gameState == GameState::Win)) {
					this->initGame();
					this->gameState = GameState::Running;
				}
				else if (this->gameState == GameState::GameOver || this->gameState == GameState::End) {
					points = 0;
					levelsPlayed = 0;
					fishBulletDelay = 2.8f; //2.8f - 1.f
					playerBulletDelay = 0.3f; //0.3f - 1.f
					this->windowTint.setFillColor(sf::Color(0, 0, 0, 0));
					this->gameState = GameState::Menu;
				}
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
			points += 10;
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

void Game::updateVariables() {
	points += DEPTH_LEVELS[this->levelsPlayed];
	this->levelsPlayed++;
	fishBulletDelay -= 0.2f;
	this->windowTint.setFillColor(sf::Color(0, 0, 0, 25.5 * this->levelsPlayed));
	if (this->levelsPlayed > 4)
		playerBulletDelay += 0.2f;
}

void Game::update() {
	this->pollEvents();
	switch (this->gameState) {
	case GameState::Running:
		this->updateColisions();
		this->player->update();
		this->enemies->update();
		this->pointsText.setString(L"Punkty: " + std::to_wstring(points));
		this->depthText.setString(L"Głębokość: " + std::to_wstring(DEPTH_LEVELS[this->levelsPlayed]) + L" m p.p.m.");

		if (this->enemies->getCount() == 0) {
			if (levelsPlayed < 9) {
				this->gameState = GameState::Win;
			}
			else {
				this->gameState = GameState::End;
			}
			this->updateVariables();
		}
		break;
	}
}

void Game::renderMessage() {
	sf::Texture aKeyTexture, dKeyTexture, leftArrTexture, rightArrTexture, spacebarTexture;
	aKeyTexture.loadFromFile("Assets/Images/aButton.png");
	dKeyTexture.loadFromFile("Assets/Images/dButton.png");
	leftArrTexture.loadFromFile("Assets/Images/leftArr.png");
	rightArrTexture.loadFromFile("Assets/Images/rightArr.png");
	spacebarTexture.loadFromFile("Assets/Images/spacebar.png");
	sf::Sprite aKey(aKeyTexture), dKey(dKeyTexture), leftArrKey(leftArrTexture), rightArrKey(rightArrTexture), spacebarKey(spacebarTexture);

	switch (this->gameState) {
	case GameState::Menu:
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
		this->gameMessage.setOutlineThickness(1.f);

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

		aKey.setPosition(230.f, 385.f);
		this->window->draw(aKey);
		
		dKey.setPosition(275.f, 385.f);
		this->window->draw(dKey);

		leftArrKey.setPosition(330.f, 385.f);
		this->window->draw(leftArrKey);

		rightArrKey.setPosition(375.f, 385.f);
		this->window->draw(rightArrKey);

		this->gameMessage.setString(L"Strzelanie:");
		this->gameMessage.setPosition(sf::Vector2f(10.f, 450.f));
		this->window->draw(gameMessage);

		spacebarKey.setPosition(sf::Vector2f(200.f, 455.f));
		this->window->draw(spacebarKey);

		//Rozpocznij
		this->gameMessage.setString(L"Powodzenia!");
		this->gameMessage.setPosition(sf::Vector2f(309.f, 525.f));
		this->window->draw(gameMessage);

		spacebarKey.setPosition(sf::Vector2f(290.f, 730.f));
		this->gameMessage.setString(L"Naciśnij         aby rozpocząć");
		this->gameMessage.setPosition(sf::Vector2f(145.f, 725.f));
		this->window->draw(gameMessage);
		this->window->draw(spacebarKey);
		break;

	case GameState::Win:
		this->gameMessage.setCharacterSize(48);
		this->gameMessage.setFont(gameFont1);
		this->gameMessage.setString(L"Wygrałeś");
		this->gameMessage.setPosition(sf::Vector2f(211.f, 280.f));
		this->window->draw(gameMessage);

		this->gameMessage.setCharacterSize(24);
		this->gameMessage.setFont(gameFont1);
		this->gameMessage.setString(L"Punkty: " + std::to_wstring(points));
		this->gameMessage.setPosition(sf::Vector2f(30.f, 400.f));
		this->window->draw(gameMessage);

		this->gameMessage.setString(L"Poziom: " + std::to_wstring(DEPTH_LEVELS[this->levelsPlayed-1]) + L" m p.p.m.");
		this->gameMessage.setPosition(sf::Vector2f(30.f, 450.f));
		this->window->draw(gameMessage);

		this->gameMessage.setCharacterSize(42);
		this->gameMessage.setFont(gameFont2);
		this->gameMessage.setStyle(sf::Text::Regular);
		this->gameMessage.setOutlineThickness(0.7f);
		spacebarKey.setPosition(sf::Vector2f(273.f, 730.f));
		this->gameMessage.setString(L"Naciśnij         aby kontynuować");
		this->gameMessage.setPosition(sf::Vector2f(127.f, 725.f));
		this->window->draw(gameMessage);
		this->window->draw(spacebarKey);


		break;

	case GameState::GameOver:
		this->gameMessage.setCharacterSize(48);
		this->gameMessage.setFont(gameFont1);
		this->gameMessage.setString(L"Koniec gry");
		this->gameMessage.setPosition(sf::Vector2f(163.f, 280.f));
		this->window->draw(gameMessage);

		this->gameMessage.setCharacterSize(24);
		this->gameMessage.setFont(gameFont1);
		this->gameMessage.setString(L"Punkty: " + std::to_wstring(points));
		this->gameMessage.setPosition(sf::Vector2f(30.f, 400.f));
		this->window->draw(gameMessage);

		this->gameMessage.setString(L"Poziom: " + std::to_wstring(DEPTH_LEVELS[this->levelsPlayed]) + L" m p.p.m.");
		this->gameMessage.setPosition(sf::Vector2f(30.f, 450.f));
		this->window->draw(gameMessage);

		this->gameMessage.setCharacterSize(42);
		this->gameMessage.setFont(gameFont2);
		this->gameMessage.setOutlineThickness(0.7f);
		spacebarKey.setPosition(sf::Vector2f(315.f, 730.f));
		this->gameMessage.setString(L"Naciśnij         aby wrócić");
		this->gameMessage.setPosition(sf::Vector2f(170.f, 725.f));
		this->window->draw(gameMessage);
		this->window->draw(spacebarKey);
		break;

		case GameState::End:
			this->gameMessage.setCharacterSize(28);
			this->gameMessage.setFont(gameFont1);
			this->gameMessage.setString(L"Dotarłeś na dno oceanu!");
			this->gameMessage.setPosition(sf::Vector2f(75.f, 280.f));
			this->window->draw(gameMessage);

			this->gameMessage.setCharacterSize(24);
			this->gameMessage.setFont(gameFont1);
			this->gameMessage.setString(L"Punkty: " + std::to_wstring(points));
			this->gameMessage.setPosition(sf::Vector2f(30.f, 400.f));
			this->window->draw(gameMessage);

			this->gameMessage.setString(L"Poziom: " + std::to_wstring(DEPTH_LEVELS[this->levelsPlayed-1]) + L" m p.p.m.");
			this->gameMessage.setPosition(sf::Vector2f(30.f, 450.f));
			this->window->draw(gameMessage);

			this->gameMessage.setCharacterSize(42);
			this->gameMessage.setFont(gameFont2);
			this->gameMessage.setOutlineThickness(0.7f);
			spacebarKey.setPosition(sf::Vector2f(315.f, 730.f));
			this->gameMessage.setString(L"Naciśnij         aby wrócić");
			this->gameMessage.setPosition(sf::Vector2f(170.f, 725.f));
			this->window->draw(gameMessage);
			this->window->draw(spacebarKey);
			break;
		break;
	}
}

void Game::render() {
	this->window->clear();
	this->window->draw(this->windowBackground);
	this->window->draw(this->windowTint);

	//Render game window
	switch (this->gameState) {
		case GameState::Menu:;
			this->renderMessage();
			break;

		case GameState::Running:
			this->player->render(this->window);
			this->enemies->render(this->window);
			this->window->draw(this->depthText);
			this->window->draw(this->pointsText);
			break;

		case GameState::Win:
			this->renderMessage();
			break;
		case GameState::GameOver:
			this->renderMessage();
			break;
		case GameState::End:
			this->renderMessage();
			break;
	}
	this->window->display();
}