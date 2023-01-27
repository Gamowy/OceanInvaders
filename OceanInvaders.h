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
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 850;
const int FRAME_RATE = 60;

//Player
const float PLAYER_SPEED = 5.f;
const float BULLET_SPEED = 3.f;
const float BULLET_DELAY = 0.3f;

//Fishes
const float FISH_SPEED = 1.f;
const int FISH_COL = 10;
const int FISH_ROW = 6;
const float FISH_WIDTH = 56.f;
const float FISH_HEIGHT = 56.f;
const float FISH_BULLET_SPEED = 3.f;
const float FISH_BULLET_DELAY = 3.f;
const float FISH_ANIMATION_TIME = 1.f;
