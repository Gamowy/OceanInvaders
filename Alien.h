#pragma once
class Alien {
private:
	//Alien types
	int type = 0;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	//Constructor / Deconstructor
	Alien();
	virtual ~Alien();

	void initAlien(int type);
	int getType();
	sf::Vector2f getPos();
	void place(sf::Vector2f vector);
	void move(sf::Vector2f vector);
	void kill();
	bool checkWindowColision(sf::Vector2f vector);
	void render(sf::RenderTarget* target);
};