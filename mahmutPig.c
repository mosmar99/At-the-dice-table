#include "mahmutHeaders.h"

enum Status { CONTINUE, WON, LOST };
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
    enum PlayerTurn playerTurn = Human; // per lab instructions
    unsigned int pHuman = 0, pComputer = 0, pTurnHuman = 0, pTurnComputer = 0, face; // p = points
    char choice;

    while (gameState == CONTINUE) {
        face = rollDie(); 

        printf("\nThe die throw equals: %u\n", face);

        if (face == 1)
        {
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
               
        puts("\nDo you want to hold? [y/n]: ");
        fgetc(stdin);
        scanf("%c", &choice);

        if (choice == 'y')
        {
            if (playerTurn == Human)
            {
                pHuman += pTurnHuman;
                gameState = switchTurns2(gameState);
            } else {
                pComputer += pTurnComputer;
                gameState = switchTurns2(gameState);
            }
                                            
        } 

    }

}