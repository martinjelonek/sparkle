#ifndef MAPEDITORCOMPONENT_H
#define MAPEDITORCOMPONENT_H

#include "../EntityManager.h"
#include "../Entity.h"
#include "../Components/TextLabelComponent.h"
#include "../Constants.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class MapEditorComponent: public Component {
    private:
        // ********************
        // * common variables *
        // ********************

        EntityManager *manager;
        Entity *entity;
        TextLabelComponent *textLabelComponentX;
        TextLabelComponent *textLabelComponentY;
        unsigned int mapSizeX;
        unsigned int mapSizeY;
        std::string labelNameX;
        std::string labelNameY;
        std::string fontFamily;
        SDL_Rect selectedTilemap = {5, 90, 32, 32};

        // ***************
        // * click event *
        // ***************

        //buttons area
        SDL_Rect keyPlusX = {150, 38, 16, 16};
        SDL_Rect keyMinusX = {168, 38, 16, 16};
        SDL_Rect keyPlusY = {150, 68, 16, 16};
        SDL_Rect keyMinusY = {168, 68, 16, 16};

        //tilemap image area
        SDL_Rect tilemap = {5, 90, 320, 96};

        //cooldown
        unsigned int clickCooldown = 0;

        void CheckClickArea (int& mouseX, int& mouseY) {
            if(((unsigned)(mouseX - keyPlusX.x) <= (keyPlusX.w))&&((unsigned)(mouseY - keyPlusX.y) <= (keyPlusX.h)) ) {
                //button plus for x
                if (mapSizeX < MAX_TILES_X) mapSizeX++;

            } else if(((unsigned)(mouseX - keyMinusX.x) <= (keyMinusX.w))&&((unsigned)(mouseY - keyMinusX.y) <= (keyMinusX.h)) ) {
                //button minus for x
                if (mapSizeX > MIN_TILES_X) mapSizeX--;
            } else if(((unsigned)(mouseX - keyPlusY.x) <= (keyPlusY.w))&&((unsigned)(mouseY - keyPlusY.y) <= (keyPlusY.h)) ) {
                //button plus for y
                if (mapSizeY < MAX_TILES_Y) mapSizeY++;
            } else if(((unsigned)(mouseX - keyMinusY.x) <= (keyMinusY.w))&&((unsigned)(mouseY - keyMinusY.y) <= (keyMinusY.h)) ) {
                //button minus for y
                if (mapSizeY > MIN_TILES_Y) mapSizeY--;            
            } else if (((unsigned)(mouseX - tilemap.x) <= (tilemap.w))&&((unsigned)(mouseY - tilemap.y) <= (tilemap.h)) ) {
                //tilemap area
                //calculate x value
                selectedTilemap.x = (mouseX - 5) / 32;
                selectedTilemap.x = selectedTilemap.x * 32 + 5;
                selectedTilemap.y = (mouseY - 90) / 32;
                selectedTilemap.y = selectedTilemap.y * 32 + 90;
            }
        }

    public:
        MapEditorComponent (EntityManager *manager, std::string labelNameX, std::string labelNameY, int mapSizeX, int mapSizeY,
                            std::string fontFamily) {
            #ifdef DEBUG
                std::cout << "...............ADDED-MAPEDITORCOMPONENT" << std::endl;
            #endif
            this->manager = manager;
            this->labelNameX = labelNameX;
            this->labelNameY = labelNameY;
            this->mapSizeX = mapSizeX;
            this->mapSizeY = mapSizeY;
            this->fontFamily = fontFamily;
        }

        void Initialize () override {
            entity = manager->GetEntitiesByName(labelNameX);
            textLabelComponentX = entity->GetComponent<TextLabelComponent>();
            entity = manager->GetEntitiesByName(labelNameY);
            textLabelComponentY = entity->GetComponent<TextLabelComponent>();
        }

        void ProcessInput (SDL_Event& event) override {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (SDL_GetTicks() - clickCooldown > 200) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        CheckClickArea(event.button.x, event.button.y);
                        clickCooldown = SDL_GetTicks();
                    }
                }
            }
        }

        void Update (float deltaTime) override {
            #ifdef DEBUG
                std::cout << "......UPDATE-MAPEDITOR-" << this->owner->name << std::endl;
            #endif
            textLabelComponentX->SetLabelText("map size x: " + std::to_string(mapSizeX), fontFamily);
            textLabelComponentY->SetLabelText("map size y: " + std::to_string(mapSizeY), fontFamily);
        }

        void Render () override {
            #ifdef DEBUG
                std::cout << "......RENDER-MAPEDITOR-" << this->owner->name << std::endl; 
            #endif
            //tilemap selection
            SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(Game::renderer, &selectedTilemap);
        }
};

#endif