#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start(int turns, int letters) {

  char rand_letters[letters];
  char vowels[] = "aeiou";
  time_t t;
  srand((unsigned) time(&t));
  char answer[30];
  int points = 0;

  printf("Hint: type (reshuffle) to get new letters\n");

  for(int count_Turns = 0; count_Turns < turns; count_Turns++) {

    reshuffle:
    rand_letters[0] = vowels[rand() % 5];
    for(int fill_Rand_Arr = 0; fill_Rand_Arr < letters; fill_Rand_Arr++) {
      rand_letters[fill_Rand_Arr + 1] = 'a' + (rand() % 26);
    }

    printf("Turn [%d]: ", count_Turns+1);

    for(int print_Letters = 0; print_Letters < letters; print_Letters++) {
      printf("%c ", rand_letters[print_Letters]);
    }

    printf("\n");

    printf("Enter a word: ");
    scanf("%s", answer);

    if(strcmp(answer, "reshuffle") == 0){
        printf("---reshuffling---\n");
        goto reshuffle;
    }

    points += strlen(answer);
  }

  return points;
}

int settings(int *turns, int *letters) {

  int command;


  printf("SETTINGS\n-----------\nNumber of letters: (1)\nNumber of turns: (2)\nBack to main menu: (3)\n");

  do {
    printf("Enter command: ");
    scanf("%d", &command);
  } while(command > 3 || command < 1);

  printf("-----------\n");


  int count_Letters;
  int count_Turns;

  switch(command) {

  case 1:
    do {
      printf("\nTHE MAX COUNT OF LETTERS IS 30\n");
      printf("Enter number of letters (current number is %d): ", *letters);
      scanf("%d\n", &count_Letters);
    } while(count_Letters < 1 || count_Letters > 30);

    *letters = count_Letters;
    return letters;

  case 2:

    do {
      printf("\nTHE MAX COUNT OF TURNS IS 25\n");
      printf("Enter number of turns (current number is %d): ", *turns);
      scanf("%d", &count_Turns);
    } while(count_Turns < 1 || count_Turns > 25);

    *turns = count_Turns;
    return turns;

    do {
      printf("Enter number of turns (current number is %d): ", *turns);
      scanf("%d", &command);
    } while(command < 1);
    *turns = command;
    return turns;


  case 3:
    break;

    return;
  }
}



void add_Words() {

  FILE *dict;

  char current_Word[100];

  int count_Words;

  do {
    printf("\nHow many words do you want to enter: ");
    scanf("%d", &count_Words);
  } while(count_Words < 0);

  dict = fopen("../dict.txt", "a");

  for(int i = -1; i < count_Words; i++) {
    if(i == -1) {
      fgets(current_Word, sizeof(current_Word), stdin);
      continue;
    }
    printf("\nWord number[%d]: ", i+1);
    fgets(current_Word, sizeof(current_Word), stdin);
    fprintf(dict, "%s", current_Word);
  }

  fclose(dict);
}



void delete_Words() {

  FILE *dict;

  int command;

  printf("\n!!!ARE YOU SURE YOU WANT TO DELETE THE DICTIONARY!?!\n");
  printf("THIS ACTION CANNOT BE UNDONE!!!\n");
  printf("Delete dictionary: (1)\nBack to main menu: (2)\n");

  do {
    printf("Enter command: ");
    scanf("%d", &command);
  } while(command > 2 || command < 1);

  printf("-----------\n");

  switch(command) {

  case 1:
    dict = fopen("../dict.txt", "w");
    fclose(dict);
    break;
  case 2:
    break;
  }
}



void enter_Words() {

  int command;

  printf("\nWhat action do you want to perform?\n");
  printf("Add words: (1)\nDelete all words: (2)\nBack to main menu: (3)\n");

  do {
    printf("Enter command: ");
    scanf("%d", &command);
  } while(command > 3 || command < 1);

  printf("-----------\n");

  switch(command) {

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



int main() {
  int command;
  int turns = 10;
  int letters = 10;

start:
  printf(" \n\n-----------\nSCRABBLE\n-----------\n\n\n");
  printf("Start: (1)\nSettings: (2)\nEnter word: (3)\nExit: (4)\n");


  do {
    printf("Enter command: ");
    scanf("%d", &command);
  } while(command > 4 || command < 1);


  printf("-----------\n");


  switch(command) {

  case 1:
    printf("You got %d points!", start(turns, letters));
    goto start;

  case 2:
    settings(&turns, &letters);
    goto start;

  case 3:
    enter_Words();
    goto start;

  case 4:
    printf("Thank you for playing!");
  }

  return 0;
}
