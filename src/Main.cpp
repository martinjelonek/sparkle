#include <iostream>
#include "./Constants.h"
#include "./Game.h"

int main(int argc, char *args[]) {
    #ifdef DEBUG
        std::cout << ">>>SPARKLE<<<" << std::endl;
        std::cout << "START" << std::endl;
        unsigned int gameLoopCount = 0;
    #endif

    Game game;

    game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while(game.IsRunning()) {
        game.ProcessInput();
        game.Update();
        game.Render();
        #ifdef DEBUG
            gameLoopCount++;
                std::cout << std::endl;
                std::cout << "MAIN_CPP-INITIALIZE-MAIN_LOOP-------------->>> i = " << gameLoopCount << " <<<" << std::endl;
        #endif
    }

    game.Destroy();

    #ifdef DEBUG
        std::cout << "END" << std::endl;
    #endif
    
    return 0;
}