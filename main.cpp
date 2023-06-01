#include <iostream>
#include <vector>
#include "GameBoard.h"
#include "GameBoardDrawer.h"
#include "MainMenu.h"
#include "GameRunner.h"
#include <SFML/Graphics.hpp>

int main() {

    MainMenuShower mainMenuShower;
    if (!mainMenuShower.prepare())
        return -1;

    for( bool running = true; running ; )
    {
        switch(mainMenuShower.showMainMenuFrame())
        {
            case 0: GameRunner().runNewGame(true); break;
            case 1: GameRunner().runNewGame(false); break;
            case 2: GameRunner().runLoadedGame(); break; // load last game from a file
            case 3:; break; // highScores
            case -1:
            case 4: running = false; break;
        }
    }
    return 0;
}
