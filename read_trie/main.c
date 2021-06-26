#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_WORDS (354935)
#define INPUT_WORD_SIZE (45)

void read_trie(char *fill){

  FILE *file = fopen("../trie_file.txt", "r");
  char line[INPUT_WORD_SIZE];

  int i = 0;

  while (fgets(line, INPUT_WORD_SIZE, file))
  {

    if(line[0] == '$'){
      printf("%s\n", line);
//      fgets(fill, INPUT_WORD_SIZE, line);

      char *s = malloc(strlen(line)-1);

      memset(s, '\0', sizeof(s));

//      printf("1\n");

      strncpy(s, line + 1, strlen(line+1) - 1);

//      printf("2\n");

      printf("---- '%s'\n", s);

      fill[i] = s;

      i++;
    }
  }

  fclose(file);
}

int main(){

  char *read_trie_from_file[NUMBER_OF_WORDS];
  read_trie(read_trie_from_file);
}
