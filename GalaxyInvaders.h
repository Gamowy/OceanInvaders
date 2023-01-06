#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//Constants

//Window
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int FRAME_RATE = 60;

//Player
const float PLAYER_SPEED = 5.f;
const float BULLET_SPEED = 3.f;
const float BULLET_DELAY = 0.3f;

//Aliens
const float ALIEN_SPEED = 1.f;
const int ALIEN_COL = 10;
const int ALIEN_ROW = 6;
const float ALIEN_WIDTH = 44.f;
const float ALIEN_HEIGHT = 32.f;
const float ALIEN_BULLET_SPEED = 3.f;
const float ALIEN_BULLET_DELAY = 1.f;