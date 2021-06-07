#include <stdio.h>
#include <stdlib.h>

int settings(int *turns, int *letters){
    int command;

    printf("SETTINGS\n-----------\nNumber of letters: (1)\nNumber of turns: (2)\nBack to main menu: (3)\n");

    do{
        printf("Enter command: ");
        scanf("%d", &command);
    }while(command > 3 || command < 1);

    printf("-----------\n");
    switch(command){
        case 1: do{
            printf("Enter number of letters (current number is %d): ", *letters);
            scanf("%d", &command);
                }while(command < 1);
            *letters = command;
            return letters;

        case 2: do{
            printf("Enter number of turns (current number is %d): ", *turns);
            scanf("%d", &command);
                }while(command < 1);
            *turns = command;
            return turns;

        case 3: break;

        return;
    }
}
int main()
{
    int command, turns = 10, letters = 10;

    start:
    printf("-----------\nSCRABBLE\n-----------\n");
    printf("Start: (1)\nSettings: (2)\nEnter word: (3)\nExit: (4)\n");

    do{
        printf("Enter command: ");
        scanf("%d", &command);
    }while(command > 4 || command < 1);

    printf("-----------\n");
    switch(command){
        case 1: printf("there is no game :(\n"); goto start;
        case 2: settings(&turns, &letters); goto start;
        case 3: printf("entering...\n"); goto start;
        case 4: printf("Thank you for playing!"); exit(0);
    }

    return 0;
}
