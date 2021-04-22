#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"
#include "../Constants.h"

class TextLabelComponent: public Component {
    private:
        SDL_Rect position;
        std::string text;
        std::string fontFamily;
        SDL_Color color;
        SDL_Texture* texture;
    public:
        TextLabelComponent(int x, int y, std::string text, std::string fontFamily, std::string color) {
            #ifdef DEBUG
                std::cout << "...............ADDED-TEXTLABELCOMPONENT: x = " << x 
                    << ", y = " << y 
                    << ", text = " << text
                    << ", fontFamily = " << fontFamily
                    << ", color = " << color
                    << std::endl;
            #endif
            this->position.x = x;
            this->position.y = y;
            this->text = text;
            this->fontFamily = fontFamily;  
            this->color = PickColor(color);
            SetLabelText(text, fontFamily);
        }

        void SetLabelText(std::string text, std::string fontFamily) {
            SDL_Surface* surface =  TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
        }

        void Render() override {
            FontManager::Draw(texture, position);
        }

        SDL_Color PickColor(std::string colorName) {
            if(colorName.compare("WHITE_COLOR") == 0){
                return WHITE_COLOR;
            } else if (colorName.compare("GREEN_COLOR") == 0) {
                return GREEN_COLOR;
            } else {
                return WHITE_COLOR;
                #ifdef DEBUG
                    std::cout << "..................WARNING: Color " << colorName << " not found, setting WHITE_COLOR instead." << std::endl;
                #endif
            }
        }
};

#endif