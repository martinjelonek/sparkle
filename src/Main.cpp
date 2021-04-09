#include <iostream>
#include "./Constants.h"
#include "./Game.h"

using namespace std;

int main(int argc, char *args[]) {
    #ifdef DEBUG
        cout << ">>>SPARKLE<<<" << endl;
        cout << "START" << endl;
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
                cout << endl;
                cout << "MAIN_CPP-INITIALIZE-MAIN_LOOP-------------->>> i = " << gameLoopCount << " <<<" << endl;
        #endif
    }

    game.Destroy();

    #ifdef DEBUG
        cout << "END" << endl;
    #endif
    return 0;
}