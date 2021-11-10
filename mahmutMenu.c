#include "mahmutHeaders.h"

// include game functions
// #include "mahmutCraps.h"
// #include "mahmutAbyss.h"
// #include "mahmutPig.h"

void craps(void);
void abyss(void);
void pig(void);

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