#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;


    // more actions to be included
    playerPos.setObjPos(14, 7, '*');     //Sets initial player position on game board
   
}


Player::~Player()
{
    // delete any heap members here
}


void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);    // Get player pos, and returns pos of my own player back to caller


    // return the reference to the playerPos arrray list
 
}


void Player::updatePlayerDir()
{
    // PPA3 input processing logic    


    switch(mainGameMechsRef->getInput())    // Get input from the GameMechs class
    {
        case '`':
            myDir = STOP;
            mainGameMechsRef->setExitTrue();    // Exit
            break;


        case 'w':
            if(myDir != DOWN)
            {
                myDir = UP;
            }
            break;


        case 'a':
            if(myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;


        case 's':
            if(myDir != UP)
            {
                myDir = DOWN;
            }
            break;


        case 'd':
            if(myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
                        // Need to add Speed Up and DOWN Somehow
        default:
            break;
    }


}


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic


    //Update Player direction/location
    switch(myDir)
    {
        case STOP:
        default:
            break;


        case LEFT:
            playerPos.x--;  
            //moveCount++;
            break;


        case RIGHT:
            playerPos.x++;
            //moveCount++;
            break;


        case UP:
            playerPos.y--;
            //moveCount++;
            break;


        case DOWN:
            playerPos.y++;
            //moveCount++;
            break;
    }


    // Border Wraparound
    if (playerPos.y == 0)
    {
        playerPos.y = (mainGameMechsRef->getBoardSizeY())-2;       //Gets Y boarder size for GameMechs class
    }
    else if (playerPos.y == (mainGameMechsRef->getBoardSizeY())-1)
    {
        playerPos.y = 1;
    }
   
    if (playerPos.x == 0)
    {
        playerPos.x = (mainGameMechsRef->getBoardSizeX())-2;    //Gets X boarder size for GameMechs class
    }
    else if (playerPos.x == (mainGameMechsRef->getBoardSizeX())-1)
    {
        playerPos.x = 1;
    }


}




