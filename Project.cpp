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

    objPos tempPos; 
    Snake_player->getPlayerPos(tempPos);    //Creates a temp position for player
    Snake->generateFood(tempPos);           // Generates initial Food using temp position
    
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
        objPos tempPlayerPos;
        Snake_player->getPlayerPos(tempPlayerPos);
        Snake->generateFood(tempPlayerPos); // Generate new food
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


    objPos foodPos;
    Snake->getFoodPos(foodPos);     // Gets food position


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

    MacUILib_printf("Score: %d\n", Snake->getScore());


    MacUILib_printf("======== DEBUG MESSAGE ========\n");


    MacUILib_printf("Board Size: %d X %d\n", Snake->getBoardSizeX(),Snake->getBoardSizeY());


    MacUILib_printf("Player Input: %c\n", Snake->getInput());    // Debug msg for current input keys


    MacUILib_printf("Player Position: %d, %d\n", playerPos.x, playerPos.y); //Prints current player position


    MacUILib_printf("Food Input: %d, %d\n", foodPos.x, foodPos.y);  //Prints current Food position


    MacUILib_printf("To Clear Food & Generate New Food, Press: 'c'\n"); //Debug message to clear and generate new food


    MacUILib_printf("Exit, Press: `\n");


    /** Uncomment After Collision Detection Implementation
    if(Snake->getLoseFlagStatus() == true || Snake->getExitFlagStatus() == true)
    {
        MacUILib_printf("Game Ended. You Scored: %d", Snake->getScore());
    }


    **/



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



