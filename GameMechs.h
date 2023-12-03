#ifndef GAMEMECHS_H
#define GAMEMECHS_H


#include <cstdlib>
#include <time.h>


#include "objPos.h"
#include "objPosArrayList.h"


using namespace std;



class GameMechs
{

    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;
       
        objPos foodPos;

        int boardSizeX;
        int boardSizeY;


    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
       
        bool getExitFlagStatus();
        bool getLoseFlagStatus();
        void setExitTrue();
        void setExitFalse();
        void setLoseFlag();


        int getScore();
        void incrementScore();


        char getInput();
        void setInput(char this_input);
        void clearInput();


        int getBoardSizeX();
        int getBoardSizeY();


        void generateFood(objPosArrayList &playerBody);
       
        // Need to accept the player boady array list
        // Go through each array list elkement to make sure they are all
        // Blocked off from random food generation  


        void getFoodPos(objPos &returnPos);


};


#endif

