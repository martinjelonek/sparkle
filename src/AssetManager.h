#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "./EntityManager.h"
#include "./TextureManager.h"
#include <map>
#include <string>

using namespace std;

class AssetManager {
    private:
        EntityManager* manager;
        map<string, SDL_Texture*> textures;
    public:
        AssetManager(EntityManager* manager);
        ~AssetManager();
        void ClearData();
        void AddTexture(string textureId, const char* filePath);
        SDL_Texture* GetTexture(string textureId);
};


#endif