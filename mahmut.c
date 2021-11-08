#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

enum Status { CONTINUE, WON, LOST };

int rollDice(void)
{
    int die1 = 1 + (rand() % 6); // pick random die1 value
    int die2 = 1 + (rand() % 6); // pick random die2 value
    // display results of this roll
    printf("Player rolled %d + %d = %d\n", die1, die2, die1 + die2);
    return die1 + die2; // return sum of dice
}

void craps(void) {
        // randomize random number generator using current time
    srand(time(NULL));
    int myPoint; // player must make this point to win
    enum Status gameStatus; // can contain CONTINUE, WON, or LOST
    int sum = rollDice(); // first roll of the dice

    // determine game status based on sum of dice
    switch(sum) {

    // win on first roll
    case 7: // 7 is a winner
    case 11: // 11 is a winner
        gameStatus = WON;
        break;

    // lose on first roll
    case 2: // 2 is a loser
    case 3: // 3 is a loser
    case 12: // 12 is a loser
        gameStatus = LOST;
        break;

    // remember point
    default:
        gameStatus = CONTINUE; // player should keep rolling
        myPoint = sum; // remember the point
        printf("Point is %d\n", myPoint);
        break; // optional
    }

    // while game not complete
    while (CONTINUE == gameStatus) { // player should keep rolling
        sum = rollDice(); // roll dice again

        // determine game status
        if (sum == myPoint) { // win by making point
            gameStatus = WON;
        }
        else {
            if (7 == sum) { // lose by rolling 7
                gameStatus = LOST;
            }
        }
    }
    // display won or lost message
    if (WON == gameStatus) { // did player win?
        puts("Player wins");
    }
    else { // player lost
        puts("Player loses");
    }
}

int main(void) {
    clock_t begin = clock();
    // --------- S T A R T  T O  C O D E  H E R E ---------
    
    craps();

    // --------- E N D  O F  C O D E
    clock_t end = clock();
    double res = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f", res);
    return 0;
}