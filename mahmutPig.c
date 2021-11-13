#include "mahmutHeaders.h"

enum Status { CONTINUE, WON, LOST };
enum PlayerTurn {HUMAN, COMPUTER};

// rolls one die
unsigned int rollDie();

// switches players between human and computer
enum PlayerTurn switchTurns2(enum PlayerTurn playerTurn) {
    switch (playerTurn)
    {
    case HUMAN:
        return COMPUTER;
    default:
        return HUMAN;
    }
}

void printPointsPlayer(enum PlayerTurn playerTurn, unsigned int pHuman, unsigned int pComputer, unsigned int pTurnHuman, unsigned int pTurnComputer, unsigned int face) {
    if (playerTurn == HUMAN)
    {   
        unsigned int oldTurnPoints = pTurnHuman - face;
        printf("\nHUMAN: %u\tCOMPUTER: %u", pHuman, pComputer);
        printf("\nHUMAN PLAYING:");
        printf("\n  The die throw equals: %u", face);        
        printf("\n  Points for Human player under current turn is: %u + %u = %u\n", oldTurnPoints, face, pTurnHuman);
    } 
    else
    {
        unsigned int oldTurnPoints = pTurnComputer - face;
        printf("\nHUMAN: %u\tCOMPUTER: %u", pHuman, pComputer);
        printf("\nCOMPUTER PLAYING:");
        printf("\n  The die throw equals: %u", face);        
        printf("\n  Points for Computer player under current turn is: %u + %u = %u\n", oldTurnPoints, face, pTurnComputer);
    }
}

void printDiceOne (enum PlayerTurn playerTurn, unsigned int pHuman, unsigned int pComputer, unsigned int face) {
        if (playerTurn == HUMAN)
    {   
        unsigned int points = 0;
        printf("\nHUMAN: %u\tCOMPUTER: %u", pHuman, pComputer);
        printf("\nHUMAN PLAYING:");
        printf("\n  The die throw equals: %u", face);        
        printf("\n  Points for Human player under current turn is: %u\n", points);
    } 
    else
    {
        unsigned int points = 0;
        printf("\nHUMAN: %u\tCOMPUTER: %u", pHuman, pComputer);
        printf("\nCOMPUTER PLAYING:");
        printf("\n  The die throw equals: %u", face);        
        printf("\n  Points for Computer player under current turn is: %u\n", points);
    }
}

void pig(void) {
    enum Status gameState = CONTINUE;
    enum PlayerTurn playerTurn = HUMAN; // per lab instructions
    unsigned int pHuman = 0, pComputer = 0, pTurnHuman = 0, pTurnComputer = 0, face; // p = points
    char choice;
    bool isNotValidInput = true;

    while (gameState == CONTINUE) {

        face = rollDie(); 

        if (face == 1)
        {
            printDiceOne(playerTurn, pHuman, pComputer, face);
            if (playerTurn == HUMAN)
            {
                pTurnHuman = 0;
            } else {
                pTurnComputer = 0;
            }
            playerTurn = switchTurns2(playerTurn);
            continue;
        } 
        else 
        {
            if (playerTurn == HUMAN) {
                pTurnHuman += face;
            } else {
                pTurnComputer += face;
            }
        }
               
        if ( pHuman >= 100 ) {
            printf("\nHUMAN WON and COMPUTER LOST!\nTHE END.");
            gameState = WON;
        } 

        if ( pComputer >= 100 ) {
            printf("\nHUMAN LOST and COMPUTER WON!\nTHE END.");
            gameState = LOST;
        } 

        printPointsPlayer(playerTurn, pHuman, pComputer, pTurnHuman, pTurnComputer, face);

        int count = 0;
        while (isNotValidInput) {
            if (count > 0) 
            {
                printf("\n--->NOT valid input. Please, enter 'y' (yes) or 'n' (no): ");
            } else  {
                printf("Do you want to hold? [y/n]: ");
            }
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'n')
            {
                isNotValidInput = false;
            }
            count++;
        }

        isNotValidInput = true;
        // printf("\nDo you want to hold? [y/n]: ");
        // scanf(" %c", &choice);

        if (choice == 'y')
        {
            if (playerTurn == HUMAN)
            {
                pHuman += pTurnHuman;
                pTurnHuman = 0;
                playerTurn = switchTurns2(playerTurn);
            } else {
                pComputer += pTurnComputer;
                pTurnComputer = 0;
                playerTurn = switchTurns2(playerTurn);
            }                                            
        } 
    }

}