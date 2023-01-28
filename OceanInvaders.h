#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


//Constants

//Depth levels 
const int DEPTH_LEVELS[10]{ 100, 500, 1000, 2000, 4000, 6000, 8000, 10000, 11000, 11034 };

//Window
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 850;
const int FRAME_RATE = 60;

//Player
//Speed of player movement
const float PLAYER_SPEED = 5.f;
//Speed of bullets for player
const float PLAYER_BULLET_SPEED = 3.f; 

//Fishes
//Speed of fish movement
const float FISH_SPEED = 1.f;
//Number of fish on screen
const int FISH_COL = 10;
const int FISH_ROW = 6;
//Size of fish sprite
const float FISH_WIDTH = 56.f;
const float FISH_HEIGHT = 56.f;
//Animation time for fish
const float FISH_ANIMATION_TIME = 1.f;
//Speed of bullets for fish
const float FISH_BULLET_SPEED = 3.f; 
