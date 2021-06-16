#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

//WINDOW
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

//TIMESTEP - DELTA TIME
const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

//EVENTS TYPE
enum EventType {
    COLLISION,
    WIN
};


//COLORS
const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color GREEN_COLOR = {0, 255, 0, 255};
const SDL_Color ORANGE_COLOR = {235, 186, 52};

//LAYERS
enum LayerType {
    TILEMAP_LAYER = 0,
    VEGETATION_LAYER = 1,
    ENEMY_LAYER = 2,
    PLAYER_LAYER = 3,
    PROJECTILE_LAYER = 4,
    UI_LAYER = 5
};
const unsigned int NUM_LAYERS = 6;

//PLAYER
const int PLAYER_SPEED = 100;

//MAP EDITOR
const unsigned int MIN_TILES_X = 20;
const unsigned int MAX_TILES_X = 100;
const unsigned int MIN_TILES_Y = 20;
const unsigned int MAX_TILES_Y = 100;

//SETTINGS (DEBUG ONLY)
#ifdef DEBUG
    const bool SHOW_COLLIDER_BOX = false;
    const bool SHOW_TRANSFORM_BOX = false;
    const bool SHOW_TEXTURE_RENDER_INFO = false; // TextureManager.cpp
#endif

#endif