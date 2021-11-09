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
    printf("\nPlayer rolled %d + %d = %d\n", die1, die2, die1 + die2);
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

void txtMenu(void) {
    char qsOne[] = "\nWhich game would you like to play?";
    char crapstxt[] = "Enter 1 for Craps";
    char abysstxt[] = "Enter 2 for The Abyss";
    char pigtxt[]   = "Enter 3 for Pig";
    char quit[]  = "Enter 0 for Quit";
    char choice[] = "Your choice? ";

    printf("%s\n  %s\n  %s\n  %s\n%s\n%s", qsOne, crapstxt, abysstxt, pigtxt, quit, choice);
}

unsigned int chooseGame(void) {
    unsigned int gameChoice;
    txtMenu();
    scanf("%u", &gameChoice);
    if (gameChoice < 0 || gameChoice > 3)
    {
        fprintf(stderr, "%s", "\n---> Please, choose among options 0 to 3:\n\n");
    }   
    return gameChoice;

}

void abyss(void) {
    /* CODE */

}

void pig(void) {
    /* CODE */

}

void launchChoice(unsigned int gameChoice){
    switch (gameChoice)
    {

    case 0:
        break;

    case 1:
        craps();
        break;

    case 2:
        abyss();
        break;

    case 3:
        pig();
        break;    

    }
}

void menu(void) {
    unsigned int gameChoice = rand(); // initialize gameChoice to a random variable for the while loop
    while (gameChoice != 0) {
        gameChoice = chooseGame(); // chooseGame filters wrong choices, if gameChoice is assigned, it must have values 0-3
        launchChoice(gameChoice);
    }
}

int main(void) {
    clock_t begin = clock();
    // --------- S T A R T  T O  C O D E  H E R E ---------
    menu();

    // --------- E N D  O F  C O D E
    clock_t end = clock();
    double res = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f", res);
    return 0;
}