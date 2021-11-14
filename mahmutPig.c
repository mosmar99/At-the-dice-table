#include "mahmutHeaders.h"

enum Status
{
    CONTINUE,
    STOP
};
enum PlayerTurn
{
    HUMAN,
    NPC
};

// rolls one die
unsigned int rollPigDie(){
    // rolling
    unsigned int r = 1 + (rand() % 6); // Returns a pseudo-random integer between 0 and RAND_MAX.

    return r;
}

// switches players between human and computer
enum PlayerTurn switchTurns2(enum PlayerTurn playerTurn)
{
    switch (playerTurn)
    {
    case HUMAN:
        return NPC;
    default:
        return HUMAN;
    }
}


_Bool checkIsOne(unsigned int face) {
    return 1 == face;
}

unsigned int updateTurnPoints(enum PlayerTurn playerTurn, unsigned int pTurnHuman, unsigned int pTurnNPC, unsigned int face) {
    switch (playerTurn)
    {
    case HUMAN:
        return pTurnHuman + face;
    
    case NPC:
        return pTurnNPC + face;

    default:
        fprintf(stderr, "\nThis game only contains two player, the human and the NPC. Error caused by ENUM overflow.\n");
        break;
        
    }
}

unsigned int updateTotPoints(enum PlayerTurn playerTurn, unsigned int pTotHuman, unsigned int pTotNPC, unsigned int pTurn) {
    switch (playerTurn)
    {
    case HUMAN:
        return pTotHuman + pTurn;
    
    case NPC:
        return pTotNPC + pTurn;

    default:
        fprintf(stderr, "\nThis game only contains two player, the human and the NPC. Error caused by ENUM overflow.\n");
        break;
        
    }
}

void printPigState(enum PlayerTurn playerTurn, unsigned int pTotHuman, unsigned int pTotNPC, unsigned int pTurnHuman, unsigned int pTurnNPC, unsigned int face) {
    if (playerTurn == HUMAN && face >= 2)
    {   
        unsigned int oldTurnPoints = pTurnHuman - face;
        printf("\nHUMAN: %u\tCOMPUTER: %u", pTotHuman, pTotNPC);
        printf("\nHUMAN PLAYING:");
        printf("\n  The die throw equals: %u", face);        
        printf("\n  Points for Human player under current turn is: %u + %u = %u\n", oldTurnPoints, face, pTurnHuman);
    } else if (playerTurn == HUMAN && face == 1){
        printf("\nHUMAN: %u\tCOMPUTER: %u", pTotHuman, pTotNPC);
        printf("\nHUMAN PLAYING:");
        printf("\n  The die throw equals: %u\n", face);        
    } else if (playerTurn == NPC && face >= 2) {
        unsigned int oldTurnPoints = pTurnNPC - face;
        printf("\nHUMAN: %u\tCOMPUTER: %u", pTotHuman, pTotNPC); 
        printf("\nCOMPUTER PLAYING:");
        printf("\n  The die throw equals: %u", face);        
        printf("\n  Points for Computer player under current turn is: %u + %u = %u\n", oldTurnPoints, face, pTurnNPC);
    } else if (playerTurn == NPC && face == 1) {
        printf("\nHUMAN: %u\tCOMPUTER: %u", pTotHuman, pTotNPC);
        printf("\nCOMPUTER PLAYING:");
        printf("\n  The die throw equals: %u\n", face);      
    } else {
        fprintf(stderr, "\n Unexpected error within \"printPigState\" function.\n");
    }
}

char promptUser(char choice) {
    int counter = 1;
    do {
        if (counter == 1)
        {
            printf("Do you want to hold (y/n): ");
            scanf(" %c", &choice);
            counter++;
        } else {
            printf("\nDo you want to hold (y/n): ");
            scanf(" %c", &choice);
        }
    } while (choice != 'y' || choice != 'n');
    return choice;
}

enum Status didSomebodyWin(unsigned int pTotHuman, unsigned int pTotNPC) {
    if (pTotHuman >= 100)
    {
        printf("\nHuman has WON.\n\n");
        return STOP;
    }
    else if (pTotNPC >= 100)
    {
        printf("\nNPC has WON.\n\n");
        return STOP;
    }
    else
    {
        return CONTINUE;
    }     
    
}

void pig(void)
{
    enum Status gameState = CONTINUE;
    enum PlayerTurn playerTurn = HUMAN;                                                       // per lab instructions
    unsigned int pTotHuman = 0, pTotNPC = 0, pTurnHuman = 0, pTurnNPC = 0, face, counter = 0, factor = 1000000, trd; // p = points
    char choice;
    float delay = 0.8;
    _Bool isOne;


    while (gameState == CONTINUE)
    {
        switch (playerTurn)
        {
        case HUMAN:
            usleep(delay * factor);
            face = rollPigDie();
            isOne = checkIsOne(face);
            if (isOne == false)
            {
                pTurnHuman = updateTurnPoints(playerTurn, pTurnHuman, pTurnNPC, face);
                printPigState(playerTurn, pTotHuman, pTotNPC, pTurnHuman, pTurnNPC, face);
                choice = promptUser(choice); // also check for invalid input, if invalid ask, ask again until valid (y/n)
                if (choice == 'y')
                {
                    pTotHuman = updateTotPoints(playerTurn, pTotHuman, pTotNPC, pTurnHuman);
                    pTurnHuman = 0;                                                        
                    playerTurn = switchTurns2(playerTurn);                         
                } // else choice was 'n', playerTurn is still HUMAN
            }
            else
            {
                usleep(delay * factor);
                printPigState(playerTurn, pTotHuman, pTotNPC, pTurnHuman, pTurnNPC, face);
                pTurnHuman = 0;
                playerTurn = switchTurns2(playerTurn);
            }
            break;

        case NPC: // there are only two players, don't need defualt
            if (counter < 2)
            {
                usleep(delay * factor);
                face = rollPigDie();
                if(checkIsOne(face) == false) {
                    pTurnNPC = updateTurnPoints(playerTurn, pTurnHuman, pTurnNPC, face);
                    printPigState(playerTurn, pTotHuman, pTotNPC, pTurnHuman, pTurnNPC, face);
                    counter++; // do first two rounds
                } else {
                    usleep(delay * factor);
                    printPigState(playerTurn, pTotHuman, pTotNPC, pTurnHuman, pTurnNPC, face);
                    pTurnNPC = 0;
                    counter = 0;
                    playerTurn = switchTurns2(playerTurn);
                }
            }
            else
            {
                trd = rand() % 2;
                if (trd == 1)
                {
                    face = rollPigDie();
                    if (checkIsOne(face) == false)
                    {
                        usleep(delay * factor);
                        pTurnNPC = updateTurnPoints(playerTurn, pTurnHuman, pTurnNPC, face);
                        printPigState(playerTurn, pTotHuman, pTotNPC, pTurnHuman, pTurnNPC, face);                    
                        pTotNPC = updateTotPoints(playerTurn, pTotHuman, pTotNPC, pTurnNPC);
                        pTurnNPC = counter = 0;
                        playerTurn = switchTurns2(playerTurn);
                    } else {
                        usleep(delay * factor);
                        printPigState(playerTurn, pTotHuman, pTotNPC, pTurnHuman, pTurnNPC, face);
                        pTurnNPC = counter = 0;
                        playerTurn = switchTurns2(playerTurn);
                    }
                } 
                else
                {
                    usleep(delay * factor);
                    pTotNPC = updateTotPoints(playerTurn, pTotHuman, pTotNPC, pTurnNPC);
                    pTurnNPC = counter = 0;
                    playerTurn = switchTurns2(playerTurn);
                }                
            }
            // the optimal is 21, 15+6=21, we don't want to roll above 21, 6+6=12<=12, atleast 2 rounds, depending on context, more will be added, // f(x)=2*x/(1+x*x)
            break;

        default:
            fprintf(stderr, "\nThis game only contains two player, the human and the NPC. Error caused by ENUM overflow.\n");
            break;

        }
        if (pTotHuman >= 100)
        {   
            usleep(delay * factor);
            printf("\nHuman has WON: POINTS = %u\n\n", pTotHuman);
            gameState = STOP;
        }

        if (pTotNPC >= 100)
        {
            usleep(delay * factor);
            printf("\nNPC has WON: POINTS = %u\n\n", pTotNPC);
            gameState = STOP;
        }
    }
}