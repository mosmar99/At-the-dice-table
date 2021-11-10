#include "mahmutHeaders.h"

enum PlayerTurn {Human, Computer};

// rolls one die
unsigned int rollDie(void) {
    
    // rolling
    unsigned int r;
    r = 1 + (rand() % 6); // Returns a pseudo-random integer between 0 and RAND_MAX.

    return r;
}

// switches players
enum PlayerTurn switchTurns(enum PlayerTurn playerTurn) {
    switch (playerTurn)
    {
    case Human:
        return Computer;
    default:
        return Human;
    }
}

void pig(void) {
    enum PlayerTurn playerTurn = Human; // per lab instructions
    unsigned int pHuman, pComputer; // p = points


    

    
}