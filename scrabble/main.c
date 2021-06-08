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


    int count_Letters;
    int count_Turns;

    switch(command){

        case 1:
          do{
            printf("Enter number of letters (current number is %d)(THE MAX COUNT OF LETTERS IS 30): ", *letters);
            scanf("%d\n", &count_Letters);
          }while(count_Letters < 1 || count_Letters > 30);

          *letters = count_Letters;
          return letters;

        case 2:
          do{
            printf("Enter number of turns (current number is %d)(THE MAX COUNT OF TURNS IS 25): ", *turns);
            scanf("%d", &count_Turns);
          }while(count_Turns < 1 || count_Turns > 25);

          *turns = count_Turns;
          return turns;

        case 3:
          break;

        return;
    }
}



void add_Words(){

  FILE *dict;

  char current_Word[100];

  int count_Words;

  do{
    printf("\nHow many words do you want to enter: ");
    scanf("%d", &count_Words);
  }while(count_Words < 0);

  dict = fopen("../dict.txt", "a");

  for(int i = -1; i < count_Words; i++){
    if(i == -1){
      fgets(current_Word, sizeof(current_Word), stdin);
      continue;
    }
      printf("\nWord number[%d]: ", i+1);
      fgets(current_Word, sizeof(current_Word), stdin);
      fprintf(dict, "%s", current_Word);
  }

  fclose(dict);
}


void delete_Words(){
  FILE *dict;
  dict = fopen("../dict.txt", "w");
  fclose(dict);
}


void enter_Words(){

  int command;

  printf("\nWhat action do you want to perform?\n");
  printf("Add words: (1)\nDelete all words: (2)\nBack to main menu: (3)\n");

  do{
        printf("Enter command: ");
        scanf("%d", &command);
    }while(command > 3 || command < 1);

    printf("-----------\n");

    switch(command){

        case 1:

          add_Words();
          break;

        case 2:

          delete_Words();
          break;

        case 3:
          break;

    }

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
          enter_Words();
          goto start;
        case 4:
          printf("Thank you for playing!");
          exit(0);
    }

    return 0;
}
