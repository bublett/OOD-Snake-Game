#ifndef PLAYER_H
#define PLAYER_H


#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"


class Player
{

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state


        Player(GameMechs* thisGMRef);
        ~Player();


        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer();


        //Lastly add self collision check
        // - If self-collided set loseFlag and exit both to true (through GM)
        // This will break the program loop and end the game


        // - If ending, you need to differentiate the end game state
        // LOST - Displayer LOST messgae
        // otherwise, displayer ENDGAME message only


    private:
        objPosArrayList *playerPosList;   // Upgrade this in iteration 3 to a List.      
        enum Dir myDir;


        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};


#endif
