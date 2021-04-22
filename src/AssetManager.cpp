#include "./AssetManager.h"
#include "./FontManager.h"
#include "./Components/TransformComponent.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager) {

}

void AssetManager::ClearData() {
    textures.clear();
    fonts.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
    fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}

TTF_Font* AssetManager::GetFont(std::string fontId) {
    #ifdef DEBUG
        std::cout << "........................CHECK-1" << std::endl;
    for(auto const &pair: fonts) {
        std::cout << "...........................map-fonts[0] = "<< pair.first << " and " << pair.second << std::endl;
    }
    #endif
    return fonts[fontId];
    #ifdef DEBUG
        std::cout << "........................CHECK-2-END" << std::endl;
    #endif
}