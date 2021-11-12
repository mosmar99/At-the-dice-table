#include "mahmutHeaders.h"

enum Status { CONTINUE, WON, LOST };
enum ISHOLD { YES, NO };
enum PlayerTurn {Human, Computer};

// rolls one die
unsigned int rollDie();

// switches players between human and computer
enum PlayerTurn switchTurns2(enum PlayerTurn playerTurn) {
    switch (playerTurn)
    {
    case Human:
        return Computer;
    default:
        return Human;
    }
}

void pig(void) {
    enum Status gameState = CONTINUE;
    enum ISHOLD isHolding = NO; 
    enum PlayerTurn playerTurn = Human; // per lab instructions
    unsigned int pHuman = 0, pComputer = 0, pTurnHuman = 0, pTurnComputer = 0, face; // p = points
    char choice;

    while (gameState == CONTINUE) {
        face = rollDie(); 

        printf("The die throw equals: %u", face);

        if (face == 1)
        {
            isHolding = NO;
            playerTurn = switchTurns2(playerTurn);
            continue;
        } 
        else 
        {
            if (playerTurn == Human) {
                pTurnHuman += face;
            } else {
                pTurnComputer += face;
            }
        }
               
        printf("%s", "Do you want to hold? [y/n]\n");
        scanf("%c", &choice);

        while (choice != 'y' || choice != 'n')
            if (choice == 'y')
            {
                isHolding = YES;
            } else {
                isHolding = NO;
            }
    }

}