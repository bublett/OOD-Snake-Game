#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000



GameMechs *Snake;
Player *Snake_player;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{
    Initialize();

    while(Snake->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}



void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    Snake = new GameMechs();
    Snake_player = new Player(Snake);  // Create an instance of player class

    objPosArrayList* tempPlayerPosList = Snake_player->getPlayerPos();  // Temp player pos list for initial random food
    objPos tempPlayerPos;
    tempPlayerPosList->getHeadElement(tempPlayerPos);
    Snake->generateFood(*tempPlayerPosList);            // Generate initial random food pos
}



void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        Snake->setInput(MacUILib_getChar());
    }

    //Debug-use key: Press 'c' to clear away current food and generate another random food
    if (Snake->getInput() == 'c')
    {
        Snake->clearInput(); // Clear current food
        objPosArrayList* tempPlayerPosList = Snake_player->getPlayerPos();

        if (tempPlayerPosList->getSize() > 0) // Check if the player position list is not empty
        {
            objPos tempPlayerPos;
            tempPlayerPosList->getHeadElement(tempPlayerPos);
            Snake->generateFood(*tempPlayerPosList);  // Pass the reference player pos list to the player's body to Generate new Food
        }
       
    }

}



void RunLogic(void)
{

    Snake_player->updatePlayerDir(); // Call the method to update player direction based on input
    Snake_player->movePlayer();      // Call the method to update player position on screen

}



void DrawScreen(void)
{

    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* playerBody = Snake_player->getPlayerPos();
    objPos tempBody;
    objPos headPos;

    objPos foodPos;
    Snake->getFoodPos(foodPos);     // Gets food position


    // Drawing the Game Board and all Game features

    for(int j=0; j<Snake->getBoardSizeY(); j++)
    {
        for(int i=0; i<Snake->getBoardSizeX(); i++)
        {
            drawn = false;     // To prevent drawing anything at the players position

            for(int k=0; k<playerBody->getSize(); k++)    // Iterate through every element in the player body list
            {
                playerBody->getElement(tempBody, k);

                if(tempBody.x == i && tempBody.y == j)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue; //If player body was drawn, don't draw anything else in the same iteration


            if(j==0 || j==Snake->getBoardSizeY()-1 || i==0 || i==Snake->getBoardSizeX()-1)   // Checks if on border
            {
                MacUILib_printf("#");
            }

            else if (j == foodPos.y && i == foodPos.x)  // Print food symbol
            {
                MacUILib_printf("%c", foodPos.symbol);
            }

            else                                // Check if not on border
            {
                MacUILib_printf(" ");
            }
        }

        MacUILib_printf("\n");
       
    }

    MacUILib_printf("Score: %d\n", Snake->getScore());                                          // Displays Current Score
    MacUILib_printf("\n");
    MacUILib_printf("======== DEBUG MESSAGE ========\n");
    MacUILib_printf("Board Size: %d X %d\n", Snake->getBoardSizeX(),Snake->getBoardSizeY());    // Displayes Game Board Size 
    
    
    switch (Snake_player->getPlayerDirection())     // Displays Player Direction
    {
        case Player::UP:
            MacUILib_printf("Player Direction: U\n");
            break;

        case Player::DOWN:
            MacUILib_printf("Player Direction: D\n");
            break;

        case Player::LEFT:
            MacUILib_printf("Player Direction: L\n");
            break;

        case Player::RIGHT:
            MacUILib_printf("Player Direction: R\n");
            break;

        case Player::STOP:
        default:
            MacUILib_printf("Player Direction: S\n");
            break;
    }
    

    playerBody->getHeadElement(headPos);
    MacUILib_printf("Player Head Position: %d, %d\n", headPos.x, headPos.y);     // Displays Snake Head Position
    MacUILib_printf("To Exit, Press: `\n");


    if (Snake->getExitFlagStatus() == true)     // Displays End Game State
    {
        MacUILib_clearScreen();


        if(Snake->getInput() == '`')
        {
            MacUILib_printf("Game Ended. \nYou Scored: %d Points", Snake->getScore());
        }
        
        else if (Snake_player->checkSelfCollision())
        {
            MacUILib_printf("YOU LOST :(\nYou Scored: %d Points", Snake->getScore());
        }
    }


}



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}



void CleanUp(void)
{
 
    MacUILib_uninit();


    //Remove Heap instances
    delete Snake;
    delete Snake_player;
   
}





