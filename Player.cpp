#include "Player.h"




Player::Player(GameMechs* thisGMRef)
{


    mainGameMechsRef = thisGMRef;
    myDir = STOP;


    objPos startPos; //Declaring starting position as an objPos
    startPos.setObjPos(14,7,'*');


    playerPosList = new objPosArrayList();   //objPos player is now of type objPosArrayList
    playerPosList->insertHead(startPos);     //The initial head of the list is the start pos.
   
}



Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}



objPosArrayList* Player::getPlayerPos()
{
    return playerPosList; //Return the reference of the player pos list
}



void Player::updatePlayerDir()
{  


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

    //Update Player direction/location

    objPos currHead; // Holds info on current head
    playerPosList->getHeadElement(currHead);
   
    switch(myDir)
    {
        case STOP:
        default:
            break;


        case LEFT:
            currHead.x--;
            break;


        case RIGHT:
            currHead.x++;
            break;


        case UP:
            currHead.y--;
            break;


        case DOWN:
            currHead.y++;
            break;
    }



    // Border Wraparound
    if (currHead.y == 0)
    {
        currHead.y = (mainGameMechsRef->getBoardSizeY())-2;       //Gets Y boarder size for GameMechs class
    }
    else if (currHead.y == (mainGameMechsRef->getBoardSizeY())-1)
    {
        currHead.y = 1;
    }
   
    if (currHead.x == 0)
    {
        currHead.x = (mainGameMechsRef->getBoardSizeX())-2;    //Gets X boarder size for GameMechs class
    }
    else if (currHead.x == (mainGameMechsRef->getBoardSizeX())-1)
    {
        currHead.x = 1;
    }


    playerPosList->insertHead(currHead);    //Inserts adjusted current position back to head
    playerPosList->removeTail();            //Removes one from tail to visualize movement of snake
   


    //Collision Detection with Food
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);


    if (currHead.x == foodPos.x && currHead.y == foodPos.y)
    {
        playerPosList->insertHead(currHead);      // Food consumed: Insert the head without removing the tail


        mainGameMechsRef->incrementScore();               // Increases score when snake collides with food
        mainGameMechsRef->generateFood(*playerPosList);   // Call generateFood to create a new food on the game board
    }
   
    else
    {
        playerPosList->removeTail();    // No food consumption: remove tail
    }


    playerPosList->insertHead(currHead);    // Ensures snake correctly displayed after food consumption
}

