#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_WORDS (354935)
#define INPUT_WORD_SIZE (45)

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

int main(){

  char *read_trie_from_file[NUMBER_OF_WORDS];
  read_trie(read_trie_from_file);

  for (int i = 0; i < NUMBER_OF_WORDS && read_trie_from_file[i]; i++) {
    printf("word[%d]: %s\n", i, read_trie_from_file[i]);
  }
}
