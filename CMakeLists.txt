cmake_minimum_required(VERSION 3.22)
project(hexagon)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare( SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        )

FetchContent_MakeAvailable(SFML)

add_executable(hexagon main.cpp Node.cpp Node.h GameBoard.cpp GameBoard.h GameBoardDrawer.cpp GameBoardDrawer.h GameBoardSerialization.cpp GameBoardSerialization.h AI.cpp AI.h MainMenu.cpp MainMenu.h GameRunner.cpp GameRunner.h GameRunner.h Dialog.cpp Dialog.h GameBoardSerialization.cpp HighScore.cpp HighScore.h HighScore.h)
target_link_libraries(hexagon sfml-graphics)