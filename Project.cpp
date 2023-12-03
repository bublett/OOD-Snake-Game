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
    Snake_player->movePlayer(); // Call the method to update player position on screen


    Snake->clearInput();

}




void DrawScreen(void)
{
    MacUILib_clearScreen();


    bool drawn;


    objPosArrayList* playerBody = Snake_player->getPlayerPos();
    objPos tempBody;


    objPos foodPos;
    Snake->getFoodPos(foodPos);     // Gets food position



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


    MacUILib_printf("Score: %d\n", Snake->getScore());


    MacUILib_printf("======== DEBUG MESSAGE ========\n");


    MacUILib_printf("Board Size: %d X %d\n", Snake->getBoardSizeX(),Snake->getBoardSizeY());


    MacUILib_printf("Player Input: %c\n", Snake->getInput());    // Debug msg for current input keys


    MacUILib_printf("Player Position:\n");


    for(int l = 0; l<playerBody->getSize();l++)
    {
        playerBody->getElement(tempBody,l);
        MacUILib_printf("<%d,%d> ", tempBody.x,tempBody.y);
    }


    MacUILib_printf("\nFood Input: %d, %d\n", foodPos.x, foodPos.y);  //Prints current Food position


    MacUILib_printf("To Clear Food & Generate New Food, Press: 'c'\n"); //Debug message to clear and generate new food


    MacUILib_printf("Exit, Press: `\n");


    if(Snake->getLoseFlagStatus() == true || Snake->getExitFlagStatus() == true)
    {
        MacUILib_printf("Game Ended. You Scored: %d", Snake->getScore());
    }


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





