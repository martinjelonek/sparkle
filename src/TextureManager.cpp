#include "./TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
    SDL_Surface* surface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);
    #ifdef DEBUG
        std::cout << ".........TEXTUREMANAGER_CPP-DRAW: x-" << sourceRectangle.x << " y-" << sourceRectangle.y << " h-" << sourceRectangle.h << " w-" << sourceRectangle.w << std::endl;
        std::cout << ".........TEXTUREMANAGER_CPP-DRAW: x-" << destinationRectangle.x << " y-" << destinationRectangle.y << " h-" << destinationRectangle.h << " w-" << destinationRectangle.w << std::endl;
    #endif
}