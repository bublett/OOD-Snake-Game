#include "GameMechs.h"


GameMechs::GameMechs()
{

    clearInput();

    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;

    boardSizeX = 30;   //Default border size
    boardSizeY = 15;

    srand(time(NULL));
    foodPos.setObjPos(-1, -1, 'o');    //Initialize foodPos outside of the game board (not displayed)
}


GameMechs::GameMechs(int boardX, int boardY)
{
    clearInput();

    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;

    boardX = boardSizeX;
    boardY = boardSizeY;

    srand(time(NULL));    
    foodPos.setObjPos(-1, -1, 'o');
}


// do you need a destructor?
GameMechs::~GameMechs()
{
    //Delete heap memebers
}



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

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}


void GameMechs::setInput(char this_input)
{
    input = this_input;
}


void GameMechs::clearInput()
{
    input = 0;
}


int GameMechs::getScore()
{
    return score;
}


void GameMechs::incrementScore()
{
    score++;
}


void GameMechs::generateFood(objPosArrayList &playerBody)
{
   
    int random_x, random_y;
    bool overlap;


    do
    {
        random_x = (rand() % (boardSizeX - 2)) + 1;     //generate random x-coord within boarder
        random_y = (rand() % (boardSizeY - 2)) + 1;     //generate random y-coord within boarder


        overlap = false;
        for (int i = 0; i < playerBody.getSize(); i++)
        {
            objPos tempBody;
            playerBody.getElement(tempBody, i);


            if (tempBody.x == random_x && tempBody.y == random_y)   // Check if the new food position overlaps
            {                                                       // with any element in the player's body
                overlap = true;
                break;
            }
        }


    } while (overlap);


    foodPos.setObjPos(random_x, random_y, 'o');     //Sets foodPos based on random coordinates


}



void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}

