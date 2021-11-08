#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void displayMainMenu(){
    puts("Which game would you like to play?");
    puts("Enter 1 for Craps");
    puts("Enter 2 for The Abyss");
    puts("Enter 3 for Pig");
    puts("Enter 0 to Quit");
}

void craps(){
    puts("craps");
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
        switch (answer){
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
                puts("\nPlease enter a valid option\n");
                break;
        }
    }    
}