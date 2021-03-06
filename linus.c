#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // sleep(unsigned int seconds)      _sleep() from stdlib.h is deprecated, but works (gives warning)
#include <time.h>

enum Status
{ // Status is ALWAYS from the perspective of the human player
    CONTINUE,
    WON,
    LOST
};

void craps();   // I added blank lines and delays in related functions to make the output more appealing and "exciting"
int rollDice(); // only used in craps
void abyss();
enum Status checkStatus(bool, unsigned int);             // apply rules 1 and 5
unsigned int checkSum(bool, unsigned int, unsigned int); // apply rules 2-4
void printAppliedRule(bool npc, unsigned int n);         // prints a message if a rule was applied
void pigs();
unsigned int pigsPlayerTurn();          // returns total points of a turn for the player
unsigned int pigsNPCTurn(unsigned int); // returns total points of a turn for the npc
void displayMainMenu();
unsigned int rollDie(bool); // roll a single die

int main()
{
    unsigned int answer;
    bool exit = false;
    while (!exit)
    {
        displayMainMenu();
        printf("%s", "Your choice? ");
        scanf("%d", &answer);
        puts("");
        switch (answer)
        {
        case 0:
            exit = true;
            break;
        case 1:
            craps();
            break;
        case 2:
            abyss();
            break;
        case 3:
            pigs();
            break;
        default:
            puts("\nPlease enter a valid option");
            break;
        }
    }
}

void craps()
{
    srand(time(NULL));

    int myPoint;
    enum Status gameStatus;
    int sum = rollDice();

    switch (sum)
    {
    case 7:
    case 11:
        gameStatus = WON;
        break;
    case 2:
    case 3:
    case 12:
        gameStatus = LOST;
        break;
    default:
        gameStatus = CONTINUE;
        myPoint = sum;
        sleep(2);
        printf("Point is %d\n", myPoint);
        break;
    }

    while (CONTINUE == gameStatus)
    {
        sum = rollDice();
        if (sum == myPoint)
        {
            gameStatus = WON;
        }
        else
        {
            if (7 == sum)
            {
                gameStatus = LOST;
            }
        }
    }

    sleep(1);
    puts("");
    if (WON == gameStatus)
    {
        puts("Player wins");
    }
    else
    {
        puts("Player loses");
    }
    sleep(2);
}

int rollDice()
{
    sleep(2);
    int die1 = 1 + (rand() % 6);
    int die2 = 1 + (rand() % 6);
    printf("Player rolled %d + %d = %d\n", die1, die2, die1 + die2);
    return die1 + die2;
}

void abyss()
{
    srand(time(NULL));

    unsigned int playerSum = 0;
    unsigned int npcSum = 0;
    enum Status gameStatus = CONTINUE;

    while (gameStatus == CONTINUE)
    { // gameplay loop
        // player's turn
        puts("");
        unsigned int die = rollDie(false); // npc = false
        sleep(1);
        if (playerSum + die <= 26)
        { // throws that yield sum > 26 doesn't count
            playerSum += die;
            playerSum = checkSum(false, playerSum, npcSum); // check rules 2-4
            printf("Player sum: %d\n\n", playerSum);
            gameStatus = checkStatus(false, playerSum); // check rules 1 and 5
            if (gameStatus != CONTINUE)
                break; // disregard npc's turn if the game is over
        }
        else
            printf("Threw discarded, yielded sum: %d\n\n", playerSum + die); // invalid throw

        // npc's turn
        die = rollDie(true); // npc = true
        sleep(1);
        if (npcSum + die <= 26)
        { // throws that yield sum > 26 doesn't count
            npcSum += die;
            npcSum = checkSum(true, npcSum, playerSum); // check rules 2-4
            printf("NPC sum: %d\n", npcSum);
            gameStatus = checkStatus(true, npcSum); // check rules 1 and 5
        }
        else
            printf("Threw discarded, yielded sum: %d\n", npcSum + die); // invalid throw
    }                                                                   // end gameplay loop

    sleep(1);
    puts("");
    gameStatus == WON ? puts("Player wins") : puts("Player loses");
    sleep(2);
}

enum Status checkStatus(bool npc, unsigned int sum)
{ // Status is ALWAYS from the perspective of the human player
    switch (sum)
    {
    case 13: // rule 1
        if (npc)
            return WON;
        return LOST;
    case 26: // rule 5
        if (npc)
            return LOST;
        return WON;
    default: // do nothing
        return CONTINUE;
    }
}

unsigned int checkSum(bool npc, unsigned int playerA, unsigned int playerB) // playerA is the individual doing the current turn, playerB is the opposing individual
{
    if (playerA >= 1 && playerA <= 12 && playerA == playerB)
    {
        printAppliedRule(npc, 0);
        return 0; // rule 2
    }
    else if (playerA >= 14 && playerA <= 24 && playerA == playerB)
    {
        printAppliedRule(npc, 12);
        return 12; // rule 3
    }
    else if (playerA == 25 && playerB == 25)
    {
        printAppliedRule(npc, 14);
        return 14; // rule 4
    }
    else
        return playerA; // do nothing
}

void printAppliedRule(bool npc, unsigned int n)
{
    sleep(1);
    if (npc)
        printf("%s", "NPC ");
    else
        printf("%s", "Player ");
    printf("back to %d points!\n", n);
    sleep(1);
}

void pigs()
{
    srand(time(NULL));

    unsigned int playerScore = 0;
    unsigned int npcScore = 0;
    enum Status gameStatus = CONTINUE;

    while (gameStatus == CONTINUE)
    { // gameplay loop
        // player's turn
        sleep(1);
        puts("-----Your turn-----");
        playerScore += pigsPlayerTurn(); // do a turn
        printf("Player score: %d\n", playerScore);
        if (playerScore >= 100)
        {
            gameStatus = WON;
            break; // disregard npc's turn if the game is over
        }

        // npc's turn
        sleep(1);
        puts("\n\n-----NPC's turn-----");
        sleep(1);
        npcScore += pigsNPCTurn(npcScore); // do a turn (argument used to enhance the NPCs strategy)
        sleep(1);
        printf("NPC score: %d\n\n\n", npcScore);
        if (npcScore >= 100)
            gameStatus = LOST;
    } // end gameplay loop

    sleep(1);
    gameStatus == WON ? puts("\nPlayer wins") : puts("\nPlayer loses");
    sleep(2);
}

unsigned int pigsPlayerTurn()
{
    unsigned int die;
    unsigned int playerTurnTotal = 0;

    while (true)
    {
        sleep(1);
        printf("%s", "Do you wish to hold? (1: Yes, 0: No) ");
        unsigned int answer;
        scanf("%d", &answer);
        if (answer != 0)
            return playerTurnTotal; // rule 3
        die = rollDie(false);
        if (die == 1)
        {
            printf("Total: %d\n\n", 0);
            return 0; // rule 1
        }
        playerTurnTotal += die; // rule 2
        printf("Total: %d\n\n", playerTurnTotal);
    }
}

unsigned int pigsNPCTurn(unsigned int sum)
{
    unsigned int die;
    unsigned npcTurnTotal = 0;

    for (unsigned int i = 0; i < 2; i++)
    { // roll two times
        if (npcTurnTotal + sum >= 100)
            return npcTurnTotal; // if the turns accumulated score is enough to win, it
        die = rollDie(true);     // stops rolling dice (guaranteed win for the computer if this executes)
        if (die == 1)
        {
            printf("Total: %d\n\n", 0);
            return 0;
        }
        npcTurnTotal += die; // rule 2
        printf("Total: %d\n\n", npcTurnTotal);
    }

    unsigned int bin = rand() % 2; // bin = [0,1]
    if (bin)
    { // roll a third time based on a 50% chance
        die = rollDie(true);
        if (die == 1)
        {
            printf("Total: %d\n\n", 0);
            return 0; // rule 1
        }
        npcTurnTotal += die; // rule 2
        printf("Total: %d\n\n", npcTurnTotal);
    }
    return npcTurnTotal;
}

void displayMainMenu()
{
    puts("\n\nWhich game would you like to play?");
    puts("  Enter 1 for Craps");
    puts("  Enter 2 for The Abyss");
    puts("  Enter 3 for Pig");
    puts("  Enter 0 to Quit");
}

unsigned int rollDie(bool npc)
{
    sleep(2);
    int die = 1 + (rand() % 6); // die = [1,6]
    if (npc)
        printf("%s", "NPC"); // prints correct output depending on if the player or the computer rolled the die
    else
        printf("%s", "Player");
    printf(" rolled %d\n", die);
    return die;
}
