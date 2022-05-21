#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const std::string WINDOW_TITLE = "GunBound";

const int widthCharacter = 120;
const int heightCharacter = 160;
const int maxWinSpeed = 31;

TTF_Font *font;