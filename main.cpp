#include <iostream>
#include <vector>
#include "GameBoard.h"
#include "GameBoardDrawer.h"
#include "MainMenu.h"
#include "GameRunner.h"
#include "Dialog.h"
#include "HighScore.h"
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
            case 2: GameRunner().runLoadedGame(); break;
            case 3: HighScore().showHighScoreFrame(); break;
            case -1:
            case 4: running = false; break;
        }
    }
    return 0;
}