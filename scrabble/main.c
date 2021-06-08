#include <stdio.h>
#include <stdlib.h>

int validation(char letters[], char word[]){

}

int start(int turns, int letters){

    char rand_letters[letters];
    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i < turns; i++){

        for(int j = 0; j < letters; j++){
            rand_letters[j] = 'a' + (rand() % 26);
        }

        printf("Turn [%d]: ", i+1);

        for(int k = 0; k < letters; k++){
            printf("%c ", rand_letters[k]);
        }

        printf("\n");
    }
}

int settings(int *turns, int *letters){

    int command;


    printf("SETTINGS\n-----------\nNumber of letters: (1)\nNumber of turns: (2)\nBack to main menu: (3)\n");

    do{
        printf("Enter command: ");
        scanf("%d", &command);
    }while(command > 3 || command < 1);

    printf("-----------\n");


    switch(command){

        case 1:
          do{
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

        case 3:
          break;

        return;
    }
}



int enter_Word(){
  printf("entering...\n");
  return;
}

int main()
{
    int command;
    int turns = 10;
    int letters = 10;


    start:
    printf(" \n\n-----------\nSCRABBLE\n-----------\n\n\n");
    printf("Start: (1)\nSettings: (2)\nEnter word: (3)\nExit: (4)\n");


    do{
        printf("Enter command: ");
        scanf("%d", &command);
    }while(command > 4 || command < 1);


    printf("-----------\n");


    switch(command){
        case 1:
          start(turns, letters);
          goto start;
        case 2:
          settings(&turns, &letters);
          goto start;
        case 3:
          enter_Word();
          goto start;
        case 4:
          printf("Thank you for playing!");
          exit(0);
    }

    return 0;
}
