#include <iostream>
#include "./Constants.h"
#include "./Game.h"

int main(int argc, char *args[]) {
    #ifdef DEBUG
        std::cout << ">>>SPARKLE<<<" << std::endl;
        unsigned int gameLoopCount = 0;
    #endif

    Game game;

    game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while(game.IsRunning()) {
        #ifdef DEBUG
                std::cout << "......MAINLOOP" << std::endl;
        #endif
        game.ProcessInput();
        #ifdef DEBUG
                std::cout << "......AFTERPROCESS" << std::endl;
        #endif
        game.Update();
        #ifdef DEBUG
                std::cout << "......AFTERUPDATE" << std::endl;
        #endif
        game.Render();
        #ifdef DEBUG
                std::cout << "......AFTERRENDER" << std::endl;
        #endif
        #ifdef DEBUG
            gameLoopCount++;
                std::cout << std::endl;
                std::cout << "...MAIN_CPP::INITIALIZE-MAIN-LOOP-------------->>> i = " << gameLoopCount << " <<<" << std::endl;
        #endif
    }

    game.Destroy();

    #ifdef DEBUG
        std::cout << "...MAIN_CPP::INITIALIZE-MAIN-LOOP-------------->>> END" << std::endl;
        std::cout << ">>>THE END<<<";
    #endif
    
    return 0;
}