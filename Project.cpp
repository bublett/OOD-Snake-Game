#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

//bool exitFlag;

GameMechs *Snake;


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
    if(Snake->getInput() != 0)  // if not null character
    {
        switch(Snake->getInput())
        {                      
            case '/':  // exit
                Snake->setExitTrue();
                break;
            case 'w':
              
                break;
            // Add more key processing here
            case 'a':
          
                break;
            // Add more key processing here
            case 's':

                break;
            // Add more key processing here
            case 'd':

                break;
            default:
                break;
        }
        Snake->clearInput();
    }

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int i,j;    

    for(j=0;j<10;j++)
    {
        for(i=0;i<20;i++)
        {
            if(j==0 || j==9 || i==0 || i==19)
            {
                MacUILib_printf("#");
            }
            
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
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
}
