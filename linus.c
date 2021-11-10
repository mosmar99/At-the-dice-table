#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // sleep(unsigned int seconds)
#include <time.h>

enum Status {CONTINUE, WON, LOST};

void craps();
void abyss();
void pigs();
void displayMainMenu();
int rollDice();
unsigned int rollDie(bool);
unsigned int pigsPlayerTurn();  // returns total points for a turn
unsigned int pigsNPCThrow();
unsigned int pigsNPCTurn(); // returns total points for a turn

int main(){
    unsigned int answer;
    bool exit = false;
    while(!exit){
        displayMainMenu();
        printf("Your choice? ");
        scanf("%d",&answer);
        puts("");
        switch(answer){
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
                puts("Please enter a valid option");
                break;
        }
    }    
}

void craps(){   // I added blank lines and delays in related functions to make the output more appealing and "exciting"
    srand(time(NULL));
    
    int myPoint;
    enum Status gameStatus;
    int sum = rollDice();

    switch(sum){
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
            printf("Point is %d\n",myPoint);
            break;
    }

    while(CONTINUE == gameStatus){
        sum = rollDice();
        if(sum == myPoint){
            gameStatus = WON;
        }else{
            if(7 == sum){
                gameStatus = LOST;
            }
        }
    }
    
    sleep(1);
    puts("");
    if(WON == gameStatus){
        puts("Player wins");
    }else{
        puts("Player loses");
    }
    sleep(2);
}

void abyss(){
    srand(time(NULL));

    unsigned int playerSum = 0;
    unsigned int npcSum = 0;
    enum Status gameStatus = CONTINUE;

    while(gameStatus == CONTINUE){  // gameplay loop
        // player's turn
        puts("");
        unsigned int die = rollDie(false);    // npc = false
        sleep(1);
        if(playerSum + die <= 26){  // throws that yield sum > 26 doesn't count
            playerSum += die;
            printf("Player sum: %d\n\n",playerSum);
            if(playerSum == 13){  // rule 1
                gameStatus = LOST;
                break;  // disregard npc's turn if game is already over
            }else if(playerSum >= 1 && playerSum <= 12 && playerSum == npcSum) playerSum = 0;   // rule 2
            else if(playerSum >= 14 && playerSum <= 24 && playerSum == npcSum) playerSum = 12;  // rule 3
            else if(playerSum == 25 && npcSum == 25) playerSum = 14;    // rule 4
            else if(playerSum == 26){    // rule 5
                gameStatus = WON;
                break;  // disregard npc's turn if game is already over
            }
        }else printf("Threw discarded, yielded sum: %d\n\n",playerSum + die);   // invalid throw

        // npc's turn
        die = rollDie(true);    // npc = true
        sleep(1);
        if(npcSum + die <= 26){ // throws that yield sum > 26 doesn't count
            npcSum += die;
            printf("NPC sum: %d\n",npcSum);
            if(npcSum == 13) gameStatus = WON;  // rule 1
            else if(npcSum >= 1 && npcSum <= 12 && npcSum == playerSum) npcSum = 0; // rule 2
            else if(npcSum >= 14 && npcSum <= 24 && npcSum == playerSum) npcSum = 12;   // rule 3
            else if(npcSum == 25 && playerSum == 25) npcSum = 14;   // rule 4
            else if(npcSum == 26) gameStatus = LOST;    // rule 5
        }else printf("Threw discarded, yielded sum: %d\n",npcSum + die);  // invalid throw
    }   // end gameplay loop

    sleep(1);
    puts("");
    gameStatus == WON ? puts("Player wins") : puts("Player loses");
    sleep(2);
}

void pigs(){
    srand(time(NULL));

    unsigned int playerScore = 0;
    unsigned int npcScore = 0;
    enum Status gameStatus = CONTINUE;

    while(gameStatus == CONTINUE){  // gameplay loop
        // player's turn
        puts("-----Your turn-----");
        playerScore += pigsPlayerTurn();
        printf("Player score: %d\n",playerScore);
        if(playerScore >= 100){
            gameStatus = WON;
            break;  // disregard npc's turn
        }

        // npc's turn
        puts("\n\n-----NPC's turn-----");
        npcScore += pigsNPCTurn();
        printf("NPC score: %d\n",npcScore);
        if(npcScore >= 100) gameStatus = LOST;
    }
}

void displayMainMenu(){
    puts("\n\nWhich game would you like to play?");
    puts("Enter 1 for Craps");
    puts("Enter 2 for The Abyss");
    puts("Enter 3 for Pig");
    puts("Enter 0 to Quit");
}

int rollDice(){
    sleep(2);
    int die1 = 1 + (rand() % 6);
    int die2 = 1 + (rand() % 6);
    printf("Player rolled %d + %d = %d\n",die1,die2,die1 + die2);
    return die1 + die2;
}

// roll single die
unsigned int rollDie(bool npc){
    sleep(2);
    int die = 1 + (rand() % 6);
    if(npc) printf("NPC");  // prints correct output depending on if the player or the computer rolled the die
    else printf("Player");
    printf(" rolled %d\n",die);
    return die;
}

unsigned int pigsPlayerTurn(){
    unsigned int die;
    unsigned int playerTurnTotal = 0;
    
    while(true){
        printf("Do you wish to hold? (1: Yes, 0: No) ");
        unsigned int answer;
        scanf("%d",&answer);
        if(answer != 0) return playerTurnTotal; // rule 3

        die = rollDie(false);
        if(die == 1) return 0;  // rule 1
        playerTurnTotal += die; // rule 2
        printf("Total: %d\n\n",playerTurnTotal);
    }
}

unsigned int pigsNPCThrow(){    // returns die value according to the rules
    unsigned int die = rollDie(true);
    if(die == 1) return 0;  // rule 1
    return die;
}

unsigned int pigsNPCTurn(){
    unsigned npcTurnTotal = 0;

    for(unsigned int i = 0; i < 2; i++){    // roll two times
        npcTurnTotal += pigsNPCThrow();    // rule 2
        printf("Total: %d\n",npcTurnTotal);
    }

    unsigned int bin = rand() % 2;  // bin = [0,1]
    if(bin) npcTurnTotal += pigsNPCThrow(); // roll a third time on a 50% chance
    printf("Total: %d\n",npcTurnTotal);
    return npcTurnTotal;
}
