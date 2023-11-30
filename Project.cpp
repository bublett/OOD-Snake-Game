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


    // Think about when to generate new food...


    //Think about whether you want to set up a debug key to call the food generation
    //routine for verifictation


    // Remeber, generateFood() requires player reference,
    //You will need to provide it AFTER player object instantioated


    //Snake->generateFood();
}


void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        Snake->setInput(MacUILib_getChar());
    }
}


void RunLogic(void)
{


    Snake_player->updatePlayerDir(); // Call the method to update player direction based on input
    Snake_player->movePlayer(); // Call the method to update player position on screen
   
    //Snake->clearInput();


}


void DrawScreen(void)
{
    MacUILib_clearScreen();


    objPos playerPos;
    Snake_player->getPlayerPos(playerPos);     //Gets player position


    // Snake->generateFood(playerPos);


    // objPos foodPos;
    // Snake->getFoodPos(foodPos);




    for(int j=0; j<Snake->getBoardSizeY(); j++)
    {
        for(int i=0;i<Snake->getBoardSizeX();i++)
        {
            if(j==0 || j==Snake->getBoardSizeY()-1 || i==0 || i==Snake->getBoardSizeX()-1)   // Checks if on border
            {
                MacUILib_printf("#");
            }
           
            else if (j == playerPos.y && i == playerPos.x)
            {
                MacUILib_printf("%c", playerPos.symbol);    // Print player symbol
            }


            // else if (j == foodPos.y && i == foodPos.x)
            // {
            //     MacUILib_printf("%c", foodPos.symbol);
            // }


            else                                // Check if not on border
            {
                MacUILib_printf(" ");
            }


        }
        MacUILib_printf("\n");
       
    }


    MacUILib_printf("Player Input: %c\n", Snake->getInput());    // Debug msg for current input keys
    //MacUILib_printf("Score %d", Snake->getScore());


}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}



void CleanUp(void)
{
    MacUILib_clearScreen();    
 
    MacUILib_uninit();


    //Remove Heap instances
    delete Snake;
    delete Snake_player;
   
}



