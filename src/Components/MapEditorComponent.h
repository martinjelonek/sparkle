#ifndef MAPEDITORCOMPONENT_H
#define MAPEDITORCOMPONENT_H

#include "../EntityManager.h"
#include "../Entity.h"
#include "../Components/TextLabelComponent.h"
#include <iostream>
#include <string>

class MapEditorComponent: public Component {
    private:
        EntityManager *manager;
        Entity *entity;
        TextLabelComponent *textLabelComponentX;
        TextLabelComponent *textLabelComponentY;
        unsigned int mapSizeX;
        unsigned int mapSizeY;
        std::string labelNameX;
        std::string labelNameY;
        std::string fontFamily;

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

        void Update (float deltaTime) override {
            #ifdef DEBUG
                std::cout << "......UPDATE-MAPEDITOR-" << this->owner->name << std::endl;
            #endif
            textLabelComponentX->SetLabelText("map size x: " + std::to_string(mapSizeX), fontFamily);
            textLabelComponentY->SetLabelText("map size y: " + std::to_string(mapSizeY), fontFamily);
        }
};

#endif