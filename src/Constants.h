#ifndef CONSTANTS_H
#define CONSTANTS_H

//WINDOW
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

//TIMESTEP - DELTA TIME
const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

/*COLLISION TYPES
enum CollisionType {
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISION,
    ENEMY_PROJECTILE_COLLISION,
    PLAYER_VEGETATION_COLLISION,
    PLAYER_LEVEL_COMPLETE_COLLISION
};
*/

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

//SETTINGS (DEBUG ONLY)
#ifdef DEBUG
    const bool SHOW_COLLIDER_BOX = true;
    const bool SHOW_TEXTURE_RENDER_INFO = false; // TextureManager.cpp
#endif

#endif