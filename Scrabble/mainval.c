#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUMBER_OF_WORDS (354935)
#define INPUT_WORD_SIZE (45)

struct trie_node_t{
    char letter;
    int is_leaf;
    struct trie_node_t *children[26];
};

struct trie_node_t *create_trie_node(){
    struct trie_node_t *new_node = malloc(sizeof(struct trie_node_t));
    new_node->is_leaf = 0;
    new_node->letter = NULL;
    for(int i = 0; i < 26; i++){
        new_node->children[i] = NULL;
    }
    return new_node;
}

int longest_word = 0;

int insert_trie_node(struct trie_node_t *root, char *word){
    struct trie_node_t *tmp = root;


    int size = find_Size(word);
    if(size - 1 > longest_word){
      longest_word = size;
    }

    int i;

    for(i = 0; i < strlen(word); i++){
        //printf("%c\n", word[i]);
        if(word[i] >= 'a' && word[i] <= 'z'){

            if(tmp->children[(word[i] - 'a')] == NULL){
                tmp->children[(word[i] - 'a')] = create_trie_node();
                tmp->children[(word[i] - 'a')]->letter = word[i];
            }
            tmp = tmp->children[(word[i] - 'a')];
        }
    }
    tmp->is_leaf = 1;
    return 1;
}

int debug(char *word){
    int i = 0;
    while(word[i] != '\n'){
        if(word[i] < 'a' || word[i] > 'z'){
            return 0;
        }
        i++;
    }

    return 1;
}

int find_Size(char *word){
    int i;
    for(i = 0; word[i] != '\n'; i++);
    //printf("\n%d\n", i);
    //printf("%s", word);
    return i;
}

void shuffle(char *word, int letters){

    char temp;
    int rand_index;

    for(int i = 0; i < letters; i++){

        rand_index = (rand() % (letters - i)) + i;
        temp = word[i];
        word[i] = word[rand_index];
        word[rand_index] = temp;
    }

    return;
}

void random_word(struct trie_node_t *root, int letters, char *word){
    struct trie_node_t *current = root;
    int random_index;
    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i < letters; i++){

        int not_null[26];
        int index_number = 0;

        for(int j = 0; j < 26; j++){

            if(current->children[j] != NULL){

                not_null[index_number] = j;
                index_number++;
            }
        }

        if(index_number > 0){
            random_index = (rand() % index_number);
            current = current->children[not_null[random_index]];
            word[i] = current->letter;

        }

        else{
            word[i] = 'a' + (rand() % 26);
        }
    }
    shuffle(word, letters);
    return;
}

int search(struct trie_node_t *root, char *word)
{
    if(root == NULL) {
        return 0;
    }

    struct trie_node_t* curr = root;

    for(int i = 0; word[i] != 0; i++){

        curr = curr->children[word[i] - 'a'];
        if(curr == NULL){
            return 0;
        }
    }

    return 1;
}

int validation(struct trie_node_t *root, char *answer, char *letters){
    int flag;

    if(strlen(answer)>strlen(letters)){

        return 0;
    }

    for(int i = 0; answer[i] != 0; i++){

        for(int j = 0; letters[j] != 0; j++){

            if(answer[i] == letters[j]){

                flag = 0;
                letters[j] ='!';
                goto located;
            }
            else{
                flag = 1;
            }
        }
        located:
        if(flag == 1){
            return 0;
        }
    }

    if(search(root, answer) == 0){
        return 0;
    }

    return 1;
}

int start(struct trie_node_t* root, int turns, int letters) {

  char rand_letters[letters];
  time_t t;
  srand((unsigned) time(&t));
  char answer[30];
  int points = 0;

  printf("Hint: type (reshuffle) to get new letters\n");

  for(int count_Turns = 0; count_Turns < turns; count_Turns++) {

    reshuffle:
    random_word(root, letters, rand_letters);
    printf("Turn [%d]: ", count_Turns+1);

    for(int print_Letters = 0; print_Letters < letters; print_Letters++) {
      printf("%c ", rand_letters[print_Letters]);
    }

    printf("\n");

    retry:
    printf("Enter a word: ");
    scanf("%s", answer);

    if(strcmp(answer, "reshuffle") == 0){
        printf("---reshuffling---\n");
        goto reshuffle;
    }

    if(validation(root, answer, rand_letters) != 1){
        printf("NOT A VALID WORD! TRY AGAIN!\n");
        goto retry;
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
      scanf("%d", &count_Letters);
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

  int word_count = 0;
  char *words[NUMBER_OF_WORDS];
  FILE *fp = fopen("Scrabble/dict.txt", "r");

  int command;
  int turns = 10;
  int letters = 10;

  if (fp == 0)
    {
        fprintf(stderr, "Dictionary missing, create \"dict.txt\" file in Scrabble folder!!!");
        exit(1);
    }

    words[word_count] = malloc(INPUT_WORD_SIZE);

    while (fgets(words[word_count], INPUT_WORD_SIZE, fp))
    {
        word_count++;
        words[word_count] = malloc(INPUT_WORD_SIZE);
    }

    struct trie_node_t *root = malloc(sizeof(struct trie_node_t));
    root = create_trie_node();


    for (int i = 0; i < NUMBER_OF_WORDS; i++)
    {
        if(debug(words[i]) != 1){
            break;
        }
        insert_trie_node(root, words[i]);

    }



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
    printf("You got %d points!", start(root, turns, letters));
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
