#ifndef MAP_H
#define MAP_H

#include "./Constants.h"
#include <string>

class Map {
    private:
        std::string textureId;
        int scale;
        int tileSize;
    public:
        Map(std::string textureId, int scale, int tileSize);
        ~Map();
        void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
        void LoadMap(std::string mapTable[MAX_TILES_X][MAX_TILES_Y]);
        void AddTile(int sourceX, int sourceY, int x, int y);
        void AddTile(std::string tileName, int sourceX, int sourceY, int x, int y);
};

#endif