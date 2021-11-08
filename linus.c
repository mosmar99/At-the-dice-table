#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // sleep(unsigned int seconds)
#include <time.h>

void displayMainMenu(){
    puts("\n\nWhich game would you like to play?");
    puts("Enter 1 for Craps");
    puts("Enter 2 for The Abyss");
    puts("Enter 3 for Pig");
    puts("Enter 0 to Quit");
}

enum Status {CONTINUE, WON, LOST};

int rollDice(){
    sleep(2);
    int die1 = 1 + (rand() % 6);
    int die2 = 1 + (rand() % 6);
    printf("Player rolled %d + %d = %d\n",die1,die2,die1 + die2);
    return die1 + die2;
}

void craps(){   // i have added blank lines and delays in related functions to make the output more appealing and exciting
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

void pigs(){
    puts("pigs");
}

void twoDicePig(){

}

void abyss(){
    puts("abyss");
}

int main(){
    int answer;
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