#include "GameMechs.h"

GameMechs::GameMechs()
{

    clearInput();

    boardSizeX = 20;
    boardSizeY = 10;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    clearInput();

    boardX = boardSizeX;
    boardY = boardSizeY;

}

// do you need a destructor?


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

void GameMechs::setExitFalse()
{
    exitFlag = 0;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}