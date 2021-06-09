#include <fstream>
#include <iostream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Components/TileComponent.h"


extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize) {
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
    std::fstream mapFile;
    mapFile.open(filePath);

    for (int y = 0; y < mapSizeY; y++) {
        for (int x = 0; x < mapSizeX; x++) {
            char ch;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tileSize;
            AddTile(sourceRectX, sourceRectY, y * (scale * tileSize), x * (scale * tileSize));
            #ifdef DEBUG
                std::cout   << ".........ADD-TILE: sRx = " << sourceRectX
                            << ", sRy = " << sourceRectX
                            << ", x = " << x * scale * tileSize
                            << ", y = " << y * scale * tileSize
                            << std::endl;
            #endif
        }
    }
    mapFile.close();
}

void Map::LoadMap(std::string mapTable[MAX_TILES_X][MAX_TILES_Y], int visibilityOffX, int visibilityOffY) {
    std::string txt;
    bool visibility;
    for (int x = 0; x < MAX_TILES_X; x++) {
        for (int y = 0; y < MAX_TILES_Y; y++) {
            txt = "TileX" + std::to_string(x) + "Y" + std::to_string(y);
            if ((x < visibilityOffX)&&(y < visibilityOffY)) {
                visibility = true;
            } else {
                visibility = false;
            }
            AddTile(txt, (mapTable[x][y][0] - 48) * tileSize, (mapTable[x][y][1] - 48) * tileSize, x * (scale * tileSize), y * (scale * tileSize), visibility);
            #ifdef DEBUG
                std::cout << ".........ADD-TILE: mapTable[x][y] = " << mapTable[x][y] << ", X = " << mapTable[x][y][0] << ", Y = " << mapTable[x][y][1] << std::endl;
            #endif
        }
    }
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y) {
    Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId, true);
}

void Map::AddTile(std::string tileName, int sourceRectX, int sourceRectY, int x, int y, bool visibility) {
    Entity& newTile(manager.AddEntity(tileName, TILEMAP_LAYER));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId, visibility);
    #ifdef DEBUG
                std::cout << "............ADD-TILE-COMPONENT: name = " << tileName << ", X = " << sourceRectX << ", Y = " << sourceRectY << std::endl;
    #endif
}