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

//Global variables
static int DEPTH = 100;
static int POINTS = 0;
static float FISH_BULLET_DELAY = 3.f; //2.8f - 1.f
static float BULLET_DELAY = 0.3f; //0.3f - 1.f

//Constants

//Window
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 850;
const int FRAME_RATE = 60;

//Player
const float PLAYER_SPEED = 5.f;
const float BULLET_SPEED = 3.f; 

//Fishes
const float FISH_SPEED = 1.f;
const int FISH_COL = 10;
const int FISH_ROW = 6;
const float FISH_WIDTH = 56.f;
const float FISH_HEIGHT = 56.f;
const float FISH_ANIMATION_TIME = 1.f;
const float FISH_BULLET_SPEED = 3.f; 
