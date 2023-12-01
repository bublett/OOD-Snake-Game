#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{

    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos startPos; //Declaring starting position as an objPos
    startPos.setObjPos(14,7,'*');

    playerPosList = new objPosArrayList(); //objPos player is now of type objPosArrayList
    playerPosList->insertHead(startPos); //The initial head of the list is the start pos.
    
    //Testing the snake visual mechanics 
    playerPosList->insertHead(startPos);
    playerPosList->insertHead(startPos);
    playerPosList->insertHead(startPos);
    playerPosList->insertHead(startPos);
}


Player::~Player()
{
    // delete any heap members here

    delete playerPosList;
}


objPosArrayList* Player::getPlayerPos(){

    return playerPosList; //Return the reference of the entire list

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

    objPos currHead; // Holds info on current head

    playerPosList->getHeadElement(currHead);
    
    switch(myDir)
    {
        case STOP:
        default:
            break;

        case LEFT:
            currHead.x--;
            //moveCount++;
            break;


        case RIGHT:
            currHead.x++;
            //moveCount++;
            break;


        case UP:
            currHead.y--;
            //moveCount++;
            break;


        case DOWN:
            currHead.y++;
            //moveCount++;
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

    playerPosList->insertHead(currHead); //Inserts adjusted current position back to head

    playerPosList->removeTail(); //Removes one from tail to visualize movement of snake


}
