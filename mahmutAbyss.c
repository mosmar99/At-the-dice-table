#include "mahmutHeaders.h"

enum PlayerTurn
{
    A,
    B
};
enum Status
{
    CONTINUE,
    WON,
    LOST
};

unsigned int rollDie(void)
{
    // rolling
    //srand(time(NULL));
    unsigned int r = 1 + (rand() % 6); // Returns a pseudo-random integer between 0 and RAND_MAX.

    return r;
}

enum PlayerTurn getWhoStarts()
{
    unsigned int r;
    r = 1 + (rand() % 2); // Returns a pseudo-random integer between 0 and RAND_MAX.

    if (r == 1)
    {
        return A;
    }
    else
    {
        return B;
    }
}

enum PlayerTurn switchTurns(enum PlayerTurn currTurn)
{
    switch (currTurn)
    {
    case A:
        return B;
    default:
        return A;
    }
}

void printState(enum PlayerTurn currTurn, unsigned int pA, unsigned int pB, unsigned int face)
{

    if (currTurn == A)
    {
        unsigned int prev = pA - face;
        printf("\nPlayer A: \n---> Current throw: %u\n---> Current sum: %u + %u = %u\n", face, prev, face, pA);
    }
    else
    {
        unsigned int prev = pB - face;
        printf("\nPlayer B:\n---> Current throw: %u\n---> Current sum: %u + %u = %u\n", face, prev, face, pB);
    }
}

char getWhoseTurn(enum PlayerTurn playerTurn)
{
    if (playerTurn == A)
    {
        return 'A';
    }
    else
    {
        return 'B';
    }
}

char getOtherPlayer(enum PlayerTurn playerTurn)
{
    if (playerTurn == A)
    {
        return 'B';
    }
    else
    {
        return 'A';
    }
}

void abyss(void)
{

    // points
    unsigned int pA = 0, pB = 0, face, factor = 1000000; // points player A, points player B, face = points on current face after die roll
    float delay = 0.8;

    // randomize who starts
    enum PlayerTurn playerTurn = getWhoStarts(); // init player who start
    enum Status gameState = CONTINUE;

    while (gameState == CONTINUE)
    {
        face = rollDie();

        if (playerTurn == A)
        {
            pA += face;
            if (pA > 26)
            {
                pA -= face;
            }
        }
        else
        {
            pB += face;
            if (pB > 26)
            {
                pB -= face;
            }
        }

        printState(playerTurn, pA, pB, face);

        usleep(delay * factor);

        if (pA == 26 || pB == 26)
        {
            char chTurn = getWhoseTurn(playerTurn);
            char chNotTurn = getOtherPlayer(playerTurn);
            printf("\nThe sum of player \"%c\" equals 26!\n---> Player \"%c\" WON and player \"%c\" LOST!\n\n", chTurn, chTurn, chNotTurn);
            gameState = WON;
        }

        if (pA == 13 || pB == 13)
        {
            char chTurn = getWhoseTurn(playerTurn);
            char chNotTurn = getOtherPlayer(playerTurn);
            printf("\nThe sum of player \"%c\" equals 13!\n---> Player \"%c\" fell into abyss and LOST! Player \"%c\" WON!\n\n", chTurn, chTurn, chNotTurn);
            gameState = LOST;
        }

        // actually its sufficient to check that one of them is in the interval since they are equal to each other, pA and pB if cond is true
        // if they points are equal, and its currPlayers turn, it means that the other player got the score first, reset currPlayers score
        if (pA == pB && ((pA >= 1 && pA <= 12) || (pB >= 1 && pB <= 12)))
        {
            if (playerTurn == A)
            {
                pA = 0;
            }
            else
            {
                pB = 0;
            }
        }

        if (pA == pB && ((pA >= 14 && pA <= 24) || (pB >= 14 && pB <= 24)))
        {
            if (playerTurn == A)
            {
                pA = 12;
            }
            else
            {
                pB = 12;
            }
        }

        // checking one is again sufficient, checking both for symmetry syntactic symmetry, good for my mental health
        if (pA == pB && (pA == 25 || pB == 25))
        {
            if (playerTurn == A)
            {
                pA = 12;
            }
            else
            {
                pB = 12;
            }
        }
        playerTurn = switchTurns(playerTurn);
    }
}
