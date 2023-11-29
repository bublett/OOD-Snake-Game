#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;


#define DELAY_CONST 100000


//bool exitFlag;


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


    Snake->setExitFalse();
}


void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        Snake->setInput(MacUILib_getChar());
    }
}


void RunLogic(void)
{


    Snake_player->updatePlayerDir(); // Call the method to update player direction based on input
    Snake_player->movePlayer(); // Call the method to update player position on screen
   

}


void DrawScreen(void)
{
    MacUILib_clearScreen();


    int i,j;  
    char game_board[10][20];    //Initializes Game Board size


    objPos playerPos;
    Snake_player->getPlayerPos(playerPos);     //Gets player position



    for(j=0;j<10;j++)
    {
        for(i=0;i<20;i++)
        {
            if(j==0 || j==9 || i==0 || i==19)   // Checks if on border
            {
                game_board[j][i] = '#';
            }
           
            else                                // Check if not on border
            {
                game_board[j][i] = ' ';
            }


            if (j == playerPos.y && i == playerPos.x)
            {
                game_board[j][i] = playerPos.symbol;    
            }


            MacUILib_printf("%c", game_board[j][i]);    //Prints game board with player symbol
        }
        MacUILib_printf("\n");
       
    }


    MacUILib_printf("Player Input: %c\n", Snake->getInput());    // Debug msg for current input keys


}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}




void CleanUp(void)
{
    MacUILib_clearScreen();    
 
    MacUILib_uninit();
    //Free memory here for Snake and Snake_player


}


