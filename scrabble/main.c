#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUMBER_OF_WORDS (100)
#define INPUT_WORD_SIZE (45)

struct trie_node_t{
    char letter;
    int is_leaf;
    struct trie_node_t *children[26];
};

int find_Size(char *word){
    int i;
    for(i = 0; word[i] != '\n'; i++);
    return i;
}

struct trie_node_t *create_trie_node(){
    struct trie_node_t *new_node = malloc(sizeof(struct trie_node_t));
    new_node->is_leaf = 0;
    new_node->letter = 0;
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


int is_Empty(struct trie_node_t *trie){

    for(int i = 0; i < 26; i++){
        if(trie->children[i] != NULL){

            return 1;
        }
    }

    return 0;
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

    if(curr->is_leaf == 1){
        return 1;
    }

    return 0;
}

int validation(struct trie_node_t *root, char answer[], char rand_letters[]){
    int flag;
    char letters[strlen(rand_letters)];

    for(int i = 0; rand_letters[i] != 0; i++){
        letters[i] = rand_letters[i];
    }

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

  if(is_Empty(root) == 0){
    return 0;
  }

  char rand_letters[letters];
  time_t t;
  srand((unsigned) time(&t));
  char answer[30];
  int points = 0;

  printf("\n\n-----------\nGAME START\n-----------\n\n\n");
  printf("Hint: type (reshuffle) to get new letters\nMAKE SURE THE WORD IS IN THE DICTIONARY; IF IT IS NOT, MAKE SURE TO ADD IT!!!\n\n");

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

int* settings(int *turns, int *letters) {

  int command;


  printf("\n\n-----------\nSETTINGS\n-----------\n\n\nNumber of letters: (1)\nNumber of turns: (2)\nBack to main menu: (3)\n");

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
    return 0;
  }
}



int add_Words() {

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
  return 1;
}



int delete_Words() {

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
    return 1;
  case 2:
    return 0;
  }
}



int enter_Words() {

  int command;

  printf("\nWhat action do you want to perform?\n\n");
  printf("Add words: (1)\nDelete all words: (2)\nBack to main menu: (3)\n");

  do {
    printf("Enter command: ");
    scanf("%d", &command);
  } while(command > 3 || command < 1);

  printf("-----------\n");

  int changed;

  switch(command) {

  case 1:
    changed = add_Words();
    break;

  case 2:
    changed = delete_Words();
    break;

  case 3:
    break;
  }

  if(changed == 1){

    return 1;
  }

  return 0;
}


void delete_Trie(struct trie_node_t *root){

    int not_null[26];
    int index_number = 0;

    for(int i = 0; i < 26; i++){

        if(root->children[i] != NULL){

            not_null[index_number] = i;
            index_number++;
        }
    }


    if(index_number > 0){
        for(int i = 0; i < index_number; i++){
            delete_Trie(root->children[not_null[i]]);
        }
    }

    for(int i = 0; i < 26; i++){
        root->children[i] = NULL;
    }

    free(root);
    root = NULL;
    return;
}

void display_Trie_in_File(FILE *trie_file, struct trie_node_t* root, char *word, int level, char *print_word){

  if(root == NULL){
    return;
  }

  fprintf(trie_file, "%s", word);

  if(root->is_leaf == 0){
    fprintf(trie_file, "%c", '\n');
//    fclose(trie_file);
  }

  if(root->is_leaf == 1){
    fprintf(trie_file, "%s", "\n$");

    for(int i = 0; i < level; i++){
      fprintf(trie_file, "%c", print_word[i]);
    }

    fprintf(trie_file, "%c", '\n');

//    fclose(trie_file);

//    for(int i = 0; word[i] != 0; i++){
//        word[i] = 32;
//    }

  }

  for(int i = 0; word[i] != 0; i++){
//      printf(">>>>>> word[%d] = %s\n", i, word);

        word[i] = 32;
    }


  for(int i = 0; i < 26; i++){
    if(root->children[i]){
      word[level] = i + 'a';
      print_word[level] = i + 'a';
    }

    for(int j = level + 1; j < INPUT_WORD_SIZE; j++){
      word[j] = 0;
    }

    display_Trie_in_File(trie_file, root->children[i], word, level + 1, print_word);
  }
}

void process_Trie_in_File(struct trie_node_t* root, char *word, int level, char *print_word){
  if(root == NULL){
    return;
  }

  FILE *trie_file = fopen("../trie_file.txt", "a");

  display_Trie_in_File(trie_file, root, word, level, print_word);

  fclose(trie_file);
}


void delete_trie_file(){
  FILE *fp = fopen("../trie_file.txt", "w");
  fclose(fp);
}

void read_trie(char **fill){

  FILE *file = fopen("../trie_file.txt", "r");
  char line[INPUT_WORD_SIZE];

  int i = 0;

  while (fgets(line, INPUT_WORD_SIZE, file))
  {
    if(line[0] == '$'){
      int lineLength = strlen(line);

      printf("line: '%s', strlen: %zu, size: %zu\n", line, lineLength, sizeof(line));

      int wordLength = lineLength - 2;
      char* s = malloc(wordLength+1);
      memcpy(s, line + 1, wordLength);
      s[wordLength] = 0;

      printf("---- fill: '%s', strlen: %zu, size: %zu\n", s, strlen(s), sizeof(s));

      fill[i] = s;

      i++;
    }
  }

  fclose(file);
}

int main() {

  int command;
  int turns = 10;
  int letters = 10;
  int score;

  redoTrie:

  printf("");
  struct trie_node_t *root = malloc(sizeof(struct trie_node_t));
  root = create_trie_node();



  int word_count = 0;
  char *words[NUMBER_OF_WORDS];
  FILE *fp = fopen("../dict.txt", "r");


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


    for (int i = 0; i < NUMBER_OF_WORDS; i++)
    {
        if(debug(words[i]) != 1){
            break;
        }
        insert_trie_node(root, words[i]);

    }

    char trie_words[INPUT_WORD_SIZE];
    char print_word[INPUT_WORD_SIZE];
    int level = 0;

    for(int i = 0; trie_words[i] != 0; i++){
        trie_words[i] = 32;
    }

    process_Trie_in_File(root, trie_words, level, print_word);
    /*char *read_trie_from_file[NUMBER_OF_WORDS];
    read_trie(read_trie_from_file);

    for (int i = 0; i < NUMBER_OF_WORDS && read_trie_from_file[i]; i++) {
      printf("word[%d]: %s\n", i, read_trie_from_file[i]);
    }*/


start:
  printf(" \n\n-----------\nSCRABBLE\n-----------\n\n\n");
  printf("Start: (1)\nSettings: (2)\nEnter word: (3)\nExit: (4)\n");


  do {
    printf("Enter command: ");
    scanf("%d", &command);
  } while(command > 4 || command < 1);


  printf("-----------\n");


  int is_Changed;

  switch(command) {

  case 1:
    system("cls");
    score = start(root, turns, letters);
    system("cls");

    if(score == 0){
        printf("THE DICTIONARY IS EMPTY!!! FILL IT IN ORDER TO PLAY!!!");
    }
    else printf("Your score is %d! Good job!", score);
    goto start;

  case 2:
    system("cls");
    settings(&turns, &letters);
    system("cls");
    goto start;

  case 3:
    system("cls");
    is_Changed = enter_Words();

    if(is_Changed == 1){
      delete_Trie(root);
      //free(trie_words);
      delete_trie_file();
      system("cls");
      goto redoTrie;
    }
    system("cls");
    goto start;

  case 4:
    system("cls");
    printf("\nThank you for playing!\n");
  }

  delete_trie_file();
  return 0;
}
